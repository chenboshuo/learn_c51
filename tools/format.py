from pathlib import Path
import re

# 日志
import logging
from rich.logging import RichHandler
# 日志设置
FORMAT = "%(message)s"
logging.basicConfig(
    level="NOTSET", format=FORMAT, datefmt="[%X]", handlers=[RichHandler()]
)
log = logging.getLogger("rich")


p = Path('./')
OPEN_SYMBOL = '#'
CLOSE_SYMBOL = '.'

code_file = p /'code.c'
formatted_file = p / 'formatted_code.c'
image_file = p / 'image_file.txt'


def code_to_image(s:str) -> str:
    """generate code from given code

    :param s: the given code snippets
    :type s: str
    :return: the image string, where `#` means OPEN led,`.` mean closed led
    :rtype: str
    """

    nums = re.findall('0x([\dCDEF]+)',s) # 抽取所有字符
    image_strs = []
    for num_str in nums:
        num = int(num_str,base=16)
        bin_str = bin(num)[2:]
        bin_str = '0'*(8-len(bin_str)) + bin_str
        bin_str = "".join(reversed(bin_str))  # 电路板接线最左边为最低位
        bin_str = bin_str.replace('0', OPEN_SYMBOL)
        bin_str = bin_str.replace('1',CLOSE_SYMBOL)
        image_strs.append(bin_str)
    return "\n".join(image_strs)

def format_code(s:str) -> str:
    """formate code by adding the image comment,
    in the comment,`#`means open,`.` means closed

    :param s: the code snippet
    :type s: str
    :return: formatted code
    :rtype: str
    """
    nums = re.findall('0x([\dCDEF]+)',s) # 抽取所有字符
    log.info(f"content:\n{s}")
    log.info(f"expect image:")
    formatted = re.sub('\n {2,}','\n  ',s) # 去掉超长缩进
    for num_str in set(nums):
        num = int(num_str,base=16)
        bin_str = bin(num)[2:]
        bin_str = '0'*(8-len(bin_str)) + bin_str
        bin_str = "".join(reversed(bin_str))  # 电路板接线最左边为最低位
        bin_str = bin_str.replace('0', OPEN_SYMBOL)
        bin_str = bin_str.replace('1',CLOSE_SYMBOL)
        log.info(bin_str)
        formatted = re.sub('('+ num_str +'),*[ \n]*',r"\1, // "+ bin_str +"\n  ",formatted)
        formatted = re.sub('('+ num_str +')};',r"\1, // "+ bin_str +"\n};",formatted)
    log.info(f"formatted:\n{formatted}")
    return formatted

if __name__ == '__main__':

    if code_file.exists():
        code_file.touch()
        s = code_file.read_text()
        formatted = format_code(s)

        formatted_file.touch()
        formatted_file.write_text(formatted)

        image_file.touch()
        image_str = code_to_image(formatted)
        image_file.write_text(image_str)
    
    if image_file.exists():
        image_str = image_file.read_text()
        formatted = image_to_code(image_str)
        formatted_file.touch()
        formatted_file.write_text(formatted)
