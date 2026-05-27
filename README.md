# Cub3D

**Cub3D** es un motor gráfico estilo *Wolfenstein 3D* implementado en **C** usando **raycasting (DDA)** y la librería **MiniLibX**. El programa lee un archivo `.cub` con la configuración (texturas/colores) y el mapa, y renderiza una vista en primera persona.

---

## Estructura del repositorio

- `mandatory/` → versión obligatoria.
- `bonus/` → versión bonus (ejecutable separado).
- `inc/` → includes y dependencia de `minilibx` (`inc/mlx`).
- `textures/`, `textures2/` → texturas `.xpm`.
- `test.cub`, `test_copy.cub` → mapas de ejemplo.
- `Makefile` → compilación (mandatory y bonus).

---

## Requisitos

### Linux
El proyecto enlaza con X11 (por MiniLibX), así que necesitas dependencias de Xorg:

- `gcc` / `cc`
- `make`
- `xorg` (headers de X11)
- `libxext-dev`
- `libbsd-dev`
- además enlaza con `-lm -lz`

> Nota: MiniLibX está incluida en `inc/mlx` y se compila desde el propio `Makefile`.

---

## Compilación

### Mandatory
```bash
make
```

Genera el ejecutable:
- `cub3D`

### Bonus
```bash
make bonus
```

Genera el ejecutable:
- `cub3D_bonus`

### Limpieza
```bash
make clean   # borra objetos
make fclean  # borra objetos + ejecutables
make re      # recompila todo
```

---

## Ejecución

```bash
./cub3D test.cub
```

(Para bonus, si aplica:)
```bash
./cub3D_bonus test.cub
```

---

## Controles (mandatory)

- `W` → avanzar  
- `S` → retroceder  
- `A` → strafe izquierda  
- `D` → strafe derecha  
- `←` → rotar a la izquierda  
- `→` → rotar a la derecha  
- `ESC` → salir  

---

## Formato del archivo `.cub`

- Texturas:
  - `NO <path>` → norte
  - `SO <path>` → sur
  - `WE <path>` → oeste
  - `EA <path>` → este

- Colores RGB (0–255):
  - `C R,G,B` → techo
  - `F R,G,B` → suelo

- Mapa:
  - `1` → pared
  - `0` → vacío
  - `N`, `S`, `E`, `W` → spawn del jugador + orientación

---

## Autor

- `isegura-` / `isegura-b`

> Proyecto realizado como parte de la escuela 42.
