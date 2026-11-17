"""
DSA Question — Set 1: Morse Code Dictionary

Description:
A Morse-code mapping table is provided, where each English alphabet character corresponds to a Morse-code representation using combinations of '.' and '-'.
Given a string written in Morse code, decode it and output a corresponding English word.
The decoded word must be present in the provided dictionary.txt file.

Dictionary constraint:
• The output word must be present in dictionary.txt.
• The word's Morse-code representation must match the given input.
• If multiple valid dictionary words can be generated, any one valid word may be printed.

Input: 
A Morse-code string is provided as input, along with the Morse-code mapping table for the alphabet.

Output: 
Print any valid word from dictionary.txt whose Morse-code representation matches the given input.
"""

MORSE_TABLE = {
    'A': '.-',    'B': '-...',  'C': '-.-.',  'D': '-..',   'E': '.',
    'F': '..-.',  'G': '--.',   'H': '....',  'I': '..',    'J': '.---',
    'K': '-.-',   'L': '.-..',  'M': '--',    'N': '-.',    'O': '---',
    'P': '.--.',  'Q': '--.-',  'R': '.-.',   'S': '...',   'T': '-',
    'U': '..-',   'V': '...-',  'W': '.--',   'X': '-..-',  'Y': '-.--',
    'Z': '--..'
}

def word_to_morse(word: str) -> str:
    return "".join(MORSE_TABLE[c.upper()] for c in word if c.isalpha())

d = {}
def convert_dict():
    with open('dictionary.txt', 'r') as f:
            for line in f:
                word = line.strip()
                morse_code = word_to_morse(word)
                d[morse_code] = word
def solve():
    convert_dict()
    input_morse = input().strip()
    if(d.get(input_morse) == None):
        print("No clue")
        return
    print(d[input_morse])





if __name__ == "__main__":
    solve()

