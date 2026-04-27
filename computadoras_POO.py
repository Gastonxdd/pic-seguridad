class Computadoras :
    def __init__(self,monitores,mouse,teclados):
        self.monitores = monitores
        self.mouse = mouse
        self.teclados = teclados
        self.encendido = False

    def arrancar(self):
        if not self.encendido:
            self.encendido = True
            print (f"los{self.monitores} y los {self.teclados} estan conecatdos")
        else:
            print("los componentes estan conectados")

    def tocar_teclado(self):
         print("click,click,click")


la_computadora = Computadoras("monitores","mouse","teclados")
print(f"la computadora tiene {la_computadora.monitores}")
la_computadora.arrancar()
la_computadora.tocar_teclado()

               
              




        