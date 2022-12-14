from automata.tm.ntm import NTM
# NTM que faz a operação de multiplicação.
ntm = NTM(
    states={'s0', 's1', 's2', 's3', 's4',
            's5', 's6', 's7', 's8', 's9', 'halt'},
    input_symbols={'0', '1', '*'},
    tape_symbols={'0', '1', '*', '#', 'E', 'Z'},
    transitions={
        's0': {
            '#': {('s0', '#', 'R')},
            '1': {('s1', '#', 'R')}
        },
        's1': {
            '*': {('s2', '1', 'R')},
            '1': {('s4', '1', 'R')}
        },
        's2': {
            'Z': {('s2', '1', 'R')},
            '1': {('s2', '1', 'R')},
            '#': {('s3', '#', 'L')}
        },
        's3': {
            '1': {('halt', '#', 'N')}
        },
        's4': {
            '1': {('s4', '1', 'R')},
            '*': {('s5', '*', 'R')}
        },
        's5': {
            '1': {('s6', 'E', 'R')},
            'Z': {('s8', 'Z', 'L')}
        },
        's6': {
            '1': {('s6', '1', 'R')},
            'Z': {('s6', 'Z', 'R')},
            '#': {('s7', 'Z', 'L')}
        },
        's7': {
            'Z': {('s7', 'Z', 'L')},
            '1': {('s7', '1', 'L')},
            'E': {('s5', 'E', 'R')}
        },
        's8': {
            'E': {('s8', '1', 'L')},
            '*': {('s9', '*', 'L')}
        },
        's9': {
            '1': {('s9', '1', 'L')},
            '#': {('s0', '#', 'R')}
        }
    },
    initial_state='s0',
    blank_symbol='#',
    final_states={'halt'}
)

ntm.validate()  # returns True

ntm.read_input_stepwise('#11*111########')

ntm.read_input('#11*111########').pop().print()

if ntm.accepts_input('#111*111#########'):
    print('accepted')
else:
    print('rejected')

palavras = ['#1*1#########', '#1*11#########', '#1111*11#########']

for w in palavras:
    print("Verificando palavra:", w)
    if ntm.accepts_input(w):
        print('aceita')
    else:
        print('rejeitada')
    ntm.read_input(w).pop().print()
