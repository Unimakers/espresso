import os
from colorama import Fore
import colorama

colorama.init(autoreset=True)


def main():
    tokenize_text()


class MOVE:
    token = "move"
    args = 2


class TURN:
    token = "turn"
    args = 1


class PICK:
    token = "pick"
    args = 0


class CAPTURE:
    token = "capture"
    args = 0


class Token:
    token: str
    type: (MOVE | TURN | PICK | CAPTURE)
    x: int | None
    y: int | None
    alpha: int | None

    def __init__(
        self, token: str, type: (MOVE | TURN | PICK | CAPTURE), *args: int | None
    ):
        self.token = token
        self.type = type
        match args.count:
            case 1:
                self.x = args[0]
            case 2:
                self.x = args[0]
                self.y = args[1]
            case 3:
                self.x = args[0]
                self.y = args[1]
                self.alpha = args[2]


keywords = ["move", "turn", "pick", "capture"]
DEBUG_LINE = 0


def tokenize_text():
    global DEBUG_LINE
    DEBUG_LINE = 0
    f = open("tools/script.eql")
    lines = f.readlines()
    for i, line in enumerate(lines):
        DEBUG_LINE += 1
        line = line.lower()
        line = line.strip("\n")
        tokens = line.split(" ")
        if keywords.count(tokens[0]) == 0:
            print_parse_error(tokens[0])
        type = get_token_type(tokens[0])
        token = assemble_command(type, tokens)  # type: ignore


def get_token_type(token: str):
    match token:
        case "move":
            return MOVE()
        case "turn":
            return TURN()
        case "pick":
            return PICK()
        case "capture":
            return CAPTURE()
    return MOVE()


def assemble_command(
    type: (MOVE | TURN | PICK | CAPTURE),
    tokens: list[str],
):
    match type.args:
        case 0:
            return Token(tokens[0], type)
        case 1:
            if len(tokens) < 2:
                return print_missing_args_error(tokens[0], type.args, len(tokens))
            return Token(type.token, type, int(tokens[1]))
        case 2:
            if len(tokens) < 3:
                return print_missing_args_error(tokens[0], type.args, len(tokens))
            return Token(type.token, type, int(tokens[1]), int(tokens[2]))
    return Token(tokens[0], type)


def print_parse_error(token: str):
    print(Fore.RED + "  ╔═════ Syntax Error : Undefined Keyword")
    print(Fore.LIGHTYELLOW_EX + "  ╠══ Line :", DEBUG_LINE)
    print(Fore.LIGHTYELLOW_EX + "  ╚══ TOKEN :", token.capitalize())
    os._exit(-1)


def print_missing_args_error(token: str, args: int, found: int):
    print(Fore.RED + "  ╔═════ Syntax Error : Missing Argument")
    print(Fore.LIGHTYELLOW_EX + "  ╠══ Line :", DEBUG_LINE)
    print(Fore.LIGHTYELLOW_EX + "  ╠══ TOKEN :", token.capitalize())
    print(Fore.LIGHTYELLOW_EX + "  ╠══ NEEDED:", args)
    print(Fore.LIGHTYELLOW_EX + "  ╚══ FOUND:", found - 1)
    os._exit(-1)


if __name__ == "__main__":
    main()
