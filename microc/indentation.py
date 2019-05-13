def firstPass(fname, spaces=4):
    with open(fname) as f:
        prevInd = 0
        for line in f:
            sline = line.lstrip()
            curInd = (len(line.expandtabs(spaces)) - len(sline))//spaces
            diff = curInd - prevInd
            print((abs(diff)*('{' if diff > 0 else '}') + (diff != 0)*' ') + sline, end='')
            prevInd = curInd

"""
SAMPLE INPUT
This is a line
    indent by one
        There's a tab here, indent two
Superdeindent
        Double indent
"""

"""
SAMPLE OUTPUT
This is a line
{ indent by one
{ There's a tab here, indent two
}} Superdeindent
{{ Idk if a double indent is even allowed in your language
"""