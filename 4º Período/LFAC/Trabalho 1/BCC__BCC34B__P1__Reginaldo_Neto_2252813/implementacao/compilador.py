# CÓDIGO ESCRITO POR: REGINALDO GREGÓRIO DE SOUZA NETO
# RA: 2252813
import sys
txt = ''
txt = sys.argv[1]
arquivo = open(txt, 'r')
entrada = arquivo.read()
buffer = []
numeros = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
palavra = ""
banco = {
    "if": "IF",
    "else": "ELSE",
    "int": "INT",
    "return": "RETURN",
    "void": "VOID",
    "while": "WHILE",
    "+": "PLUS",
    "-": "MINUS",
    "*": "TIMES",
    "/": "DIVIDE",
    "<": "LESS",
    "<=": "LESS_EQUAL",
    ">": "GREATER",
    ">=": "GREATER_EQUAL",
    "==": "EQUALS",
    "!=": "DIFFERENT",
    "(": "LPAREN",
    ")": "RPAREN",
    "[": "LBRACKETS",
    "]": "RBRACKETS",
    "{": "LBRACES",
    "}": "RBRACES",
    "=": "ATTRIBUITION",
    ";": "SEMICOLON",
    ",": "COMMA",
    "char": "CHAR",
}
esp = ""
flag = 0
for letra in entrada:
    if(letra in numeros):  # NUMERO
        if(buffer):
            buffer.append(letra)
        else:
            print("NUMBER")
    elif(flag == 1):
        if(letra == "="):
            esp += letra
        proviosria = banco.get(esp)
        print(proviosria)
        esp = ''
        flag = 0
    elif(letra == '!' or letra == '=' or letra == '>' or letra == '<'):
        flag = 1
        esp += letra
    elif(letra != " "):  # LETRA OU CARACTER ESPECIAL
        token = banco.get(letra)
        if(token):
            if(buffer):
                for pos in buffer:
                    palavra += pos
                buffer.clear()
                proviosria = banco.get(palavra)
                if(proviosria):
                    print(proviosria)
                elif(palavra != "\n"):
                    print("ID")
                buffer.clear
            print(token)
            palavra = ''
        elif(letra != '!'):
            buffer.append(letra)
    else:  # ESPAÇO
        if(buffer == ''):
            buffer = ''
        else:
            for pos in buffer:
                palavra += pos
            buffer.clear()
            if(palavra != ''):
                token = banco.get(palavra)
            if(token):
                print(token)
            palavra = ''
