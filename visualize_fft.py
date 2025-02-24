import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Substitua 'COM3' pela porta serial correta
ser = serial.Serial('COM5', 115200)

fig, ax = plt.subplots()
frequencias = ['Subgraves', 'Graves', 'Médios', 'Agudos', 'Superagudos']
amplitudes = [0] * len(frequencias)

barras = ax.bar(frequencias, amplitudes)
ax.set_ylim(0, 30)  # Ajuste conforme necessário

def animate(i):
    linha = ser.readline().decode('utf-8').strip()
    dados = [float(val) for val in linha.split(',')]
    for bar, altura in zip(barras, dados):
        bar.set_height(altura)
    return barras

ani = animation.FuncAnimation(fig, animate, interval=50)
plt.show()
