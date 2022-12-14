from automata.tm.ntm import NTM
# NTM que faz a operação de adição.
ntm = NTM(
    states={'s0', 's1', 's2', 's3', 'halt'},
    input_symbols={'0', '1', '+'},
    tape_symbols={'0', '1', '+', '#', 'E'},
    transitions={
        's0': {
            '#': {('s1', '#', 'R')}
        },
        's1': {
            'E': {('s1', 'E', 'R')},
            '+': {('s2', 'E', 'R')}
        },
        's2': {
            'E': {('s2', 'E', 'R')},
            '#': {('s3', '#', 'L')}
        },
        's3': {
            'E': {('halt', '#', 'N')}
        }
    },
    initial_state='s0',
    blank_symbol='#',
    final_states={'halt'}
)

ntm.validate()  # returns True

ntm.read_input_stepwise('#EEEEE+EE#')

ntm.read_input('#EEEEE+EE#').pop().print()

if ntm.accepts_input('#EEEEE+EE#'):
    print('accepted')
else:
    print('rejected')

palavras = ['#E+E#', '#E+EE#', '#EEEEE+EE#']

for w in palavras:
    print("Verificando palavra:", w)
    if ntm.accepts_input(w):
        print('aceita')
    else:
        print('rejeitada')
    ntm.read_input(w).pop().print()
