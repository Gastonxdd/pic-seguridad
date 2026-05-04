class Calculadora:

    def __init__(self):
        self.resultado = 0
    
    def sumar(self, n):
        self.resultado += n

    def restar(self, n):
        self.resultado -= n

    def dividir(self, n):
        if n != 0:
            self.resultado /= n
        else:
            print("err, esta mal en algo")

    def multiplicar(self, n):
        self.resultado *= n

    def limpiar(self):
        self.resultado = 0

mi_calc = Calculadora()

while True:
    print(f"\n---VALOR ACTUAL: {mi_calc.resultado}---")
    print("1.Sumar")
    print("2.Restar")
    print("3.Multiplicar")
    print("4.Dividir")
    print("5.Limpiar (poner en 0)")
    print("6.salir")

    opcion = input("\nElige una opcion: ")

    if opcion == "6":
        print("blutus dibais is disconectidos exesfulai")
        break #romper while (bucle)

    if opcion in ["1","2","3","4"]:
        num = float(input("Ingresa el número :"))

        if opcion == "1":
            mi_calc.sumar(num)
        elif opcion == "2":
            mi_calc.restar(num)
        elif opcion == "3":
            mi_calc.multiplicar(num)
        elif opcion =="4":
            mi_calc.dividir(num)

    elif opcion == "5":
        mi_calc.limpiar()

    else:
        print("\n---OPCION NO VÁLIDAAAAAAAA, ELEJí UN NÚMEROOOOOO---")



    


