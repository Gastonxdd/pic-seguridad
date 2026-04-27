#PROGRAMACIÓN ORIENTADA A OBJETOS

#
class auto :
    def __init__(self,marca,modelo,color): #__init__ crea al objeto
        self.marca = marca
        self.modelo = modelo
        self.color = color
        self.encendido = False #estado inicial

    def arrancar(self):
        if not self.encendido:
            self.encendido = True
            print (f"el {self.marca} {self.modelo}  ha arrancado")
        else:
            print("el auto ya esta encendido.")

    def tocar_bocina(self):
        print("beep, beep")


mi_auto = auto("ford","mustang","negro")

print(f"mi auto es un {mi_auto.modelo}")
mi_auto.arrancar()
mi_auto.tocar_bocina()
