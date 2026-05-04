class Calculadora:

    def __init__(self):
        self.resultado = 0
    
    def sumar(self, numero):
        self.resultado += numero
        print(f"Suma realizada, resultado:{self.resultado}")

    def mostrar(self):
        print(f"El resultado es igual a {self.resultado}")


mis_notas = Calculadora()

mis_notas.sumar(10)
mis_notas.sumar(10)

mis_notas.mostrar()