from fpdf import FPDF
from pathlib import Path

cwd = Path(__file__).parent

cwd = str(cwd)
cwd += '\data\export'

pdf = FPDF()

pdf.add_page()
pdf.add_font('Arial', '', 'c:/windows/fonts/arial.ttf', uni=True)

pdf.set_font("Arial", size=12)

path1 = cwd + '.txt'
file = open(path1, "r")

for x in file:
    pdf.cell(200, 10, txt=x, ln=1, align='L')


path2 = cwd + '.pdf'
pdf.output(path2)

file.close()
