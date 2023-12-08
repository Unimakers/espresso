from enum import Enum
import os
from colorama import Fore
import colorama

colorama.init(autoreset=True)


def main():
    parse_text()


class Token:
    token: str
    type: str
    x: int
    y: int
    alpha: int


class TokenType(Enum):
    MOVE = 1
    TURN = 2
    PICK = 3
    CAPTURE = 4


class TokenDef:
    token: str
    type: TokenType
    args: int


keywords = ["move", "turn", "pick", "capture"]


def parse_text():
    f = open("tools/script.eql")
    lines = f.readlines()
    for i, line in enumerate(lines):
        line = line.lower()
        line = line.strip("\n")
        tokens = line.split(" ")
        if keywords.count(tokens[0]) == 0:
            print_parse_error(tokens[0], i)
    print_success()


def print_parse_error(token: str, line: int):
    print(Fore.RED + "Syntax Error : Undefined Keyword")
    print(Fore.LIGHTYELLOW_EX + " ├─ Line :", line + 1)
    print(Fore.LIGHTYELLOW_EX + " └──── TOKEN :", token)
    os._exit(-1)


def print_success():
    print(Fore.LIGHTGREEN_EX + "EQL script is valid and has been parsed sucessfully !")


if __name__ == "__main__":
    main()
