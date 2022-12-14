from automata.tm.ntm import NTM
# NTM que faz a operação de subtração.
ntm = NTM(
    states={'s0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 's8', 'halt'},
    input_symbols={'0', '1', '-'},
    tape_symbols={'0', '1', '-', '#', 'E'},
    transitions={
        's0': {
            '#': {('s1', '#', 'R')}
        },
        's1': {
            'E': {('s2', '#', 'R')}
        },
        's2': {
            'E': {('s2', 'E', 'R')},
            '-': {('s3', '-', 'R')}
        },
        's3': {
            'E': {('s3', 'E', 'R')},
            '#': {('s4', '#', 'L')}
        },
        's4': {
            'E': {('s5', '#', 'L')}
        },
        's5': {
            'E': {('s6', 'E', 'L')},
            '-': {('halt', '#', 'N')}
        },
        's6': {
            'E': {('s6', 'E', 'L')},
            '-': {('s7', '-', 'L')}
        },
        's7': {
            'E': {('s8', 'E', 'L')},
            '#': {('halt', '#', 'N')}
        },
        's8': {
            'E': {('s8', 'E', 'L')},
            '#': {('s1', '#', 'R')}
        }
    },
    initial_state='s0',
    blank_symbol='#',
    final_states={'halt'}
)

ntm.validate()  # returns True

ntm.read_input_stepwise('#EEEEE-EE#')

ntm.read_input('#EEEEE-EE#').pop().print()

if ntm.accepts_input('#EEEEE-EE#'):
    print('accepted')
else:
    print('rejected')

palavras = ['#E-E#', '#E-EE#', '#EEEEE-EE#']

for w in palavras:
    print("Verificando palavra:", w)
    if ntm.accepts_input(w):
        print('aceita')
    else:
        print('rejeitada')
    ntm.read_input(w).pop().print()
