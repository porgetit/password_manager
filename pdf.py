from fpdf import FPDF

pdf = FPDF()

pdf.add_page()
pdf.add_font('Arial', '', 'c:/windows/fonts/arial.ttf', uni=True)

pdf.set_font("Arial", size=12)

file = open("D:\\Users\\xdpor\\Documents\\Estudio\\ing_de_sistemas\\segundo_semestre\\programacion_2\\proyecto_final\\data\\export.txt", "r")

for x in file:
    pdf.cell(200, 10, txt=x, ln=1, align='L')

pdf.output("D:\\Users\\xdpor\\Documents\\Estudio\\ing_de_sistemas\\segundo_semestre\\programacion_2\\proyecto_final\\data\\export.pdf")

file.close()
