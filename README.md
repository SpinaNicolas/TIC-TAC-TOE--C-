# 🎮 Tateti Los Argento (C)

Proyecto de consola desarrollado en lenguaje C que implementa el clásico juego Ta-Te-Ti (Tic Tac Toe), incorporando gestión de usuarios, persistencia en archivos y estadísticas de juego.

---

Funcionalidades

- Registro e inicio de sesión de jugadores
-  Persistencia de datos en archivos binarios
-  Modo de juego:
  - Jugador vs Jugador
  - Jugador vs CPU
-  Sistema de estadísticas:
  - Partidas jugadas
  - Victorias, derrotas y empates
  - Porcentaje de rendimiento
-  Sistema de puntos:
  - Victoria: +3 pts
  - Empate: +1 pt
  - Derrota: 0 pts
-  Modificación de username

---

## 🧱 Estructura del Proyecto

### Archivos utilizados:

- `jugadores.dat` → Almacena los jugadores
- `partidas.dat` → (estructura creada, uso parcial)
- `partidaXjugador.dat` → Relación entre jugadores y resultados

### Estructuras principales:

stJugador
stPartida
stPartidaXJugador
