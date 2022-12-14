from automata.tm.ntm import NTM
# NTM que faz a operação de divisão.
ntm = NTM(
    states={'s0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 's8', 's9', 'halt'},
    input_symbols={'0', '1', '/'},
    tape_symbols={'0', '1', '/', '#', 'E', 'Z'},
    transitions={
        's0': {
            '#': {('s1', '#', 'R')}
        },
        's1': {
            '1': {('s2', '#', 'R')},
            '/': {('s9', '#', 'R')}            
        },
        's2': {
            '1': {('s2', '1', 'R')},
            '/': {('s3', '/', 'R')}
        },
        's3': {
            '1': {('s3', '1', 'R')},
            'E': {('s3', 'E', 'R')},
            '#': {('s4', '#', 'L')},
            'Z': {('s4', 'Z', 'L')}
        },
        's4': {
            'E': {('s4', 'E', 'L')},
            '1': {('s5', 'E', 'L')}
        },
        's5': {
            '1': {('s7', '1', 'L')},
            '/': {('s6', '/', 'R')}
        },
        's6': {
            'E': {('s6', '1', 'R')},
            'Z': {('s6', 'Z', 'R')},
            '#': {('s7', 'Z', 'L')}
        },
        's7': {
            '1': {('s7', '1', 'L')},
            'Z': {('s7', 'Z', 'L')},
            '/': {('s8', '/', 'L')}
        },
        's8': {
            '1': {('s8', '1', 'L')},
            '#': {('s1', '#', 'R')}
        },
        's9': {
            'Z': {('s9', '1', 'R')},
            '1': {('s9', '#', 'R')},
            '#': {('halt', '#', 'N')}
        }       
    },
    initial_state='s0',
    blank_symbol='#',
    final_states={'halt'}
)

ntm.validate()

ntm.read_input_stepwise('#1111/11###########')

ntm.read_input('#1111/11###########').pop().print()

if ntm.accepts_input('#111111/11##############'):
    print('accepted')
else:
    print('rejected')

palavras = ['#1111/11###########','#111111/111###########','#11/11###########']

for w in palavras:
  print("Verificando palavra:", w)
  if ntm.accepts_input(w):
    print('aceita')
  else:
    print('rejeitada')
  ntm.read_input(w).pop().print()