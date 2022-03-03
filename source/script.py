import PyPDF2
from sys import argv
script, path_in, path_out = argv
pdf = open(path_in, 'rb')
pdf_f_reader = PyPDF2.PdfFileReader(pdf)
txt = open(path_out, 'w')
for page in pdf_f_reader.pages:
  txt.write(page.extractText())
txt.close()
pdf.close()