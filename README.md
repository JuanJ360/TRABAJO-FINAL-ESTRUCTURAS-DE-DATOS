# TRABAJO-FINAL-ESTRUCTURAS-DE-DATOS
Aqui se va a guardar todo el trabajo en parejas de Juan José Bolivar y Juan Andrés Correa sobre la creación del TAD monopoly para la asinatura estructuras de datos


## Primera Semana

- Juan Andrés y yo discutimos la forma en la que ibamos a trabajar con nuestro programa. En esta inciamos definiendo los .h mas importantes y separamos las casillas y cartas en cada una de sus carpetas.

- Nos estamos basando directamente con los datos en un monopoly real, usando los mismos valores de propiedad de casillas, dinero total, viviendas y más. Esto con el objetivo de no tener que balancear el juego después.

- Para esto estamos usando la pagina oficial del monopoly fandom, por ejemplo para las casas{https://monopoly.fandom.com/wiki/Houses#:~:text=El%20precio%20de%20una%20casa,y%20naranjas%20%2D%20%C2%A3%5C%24100}


## Segunda Semana

- En esta semana tuvimos menos reuniones pero se trabajó finalmente en la instanciación de la finalización de los .h, implementando los trabajos que hicimos y las cosas que debatimos en clase, en las reuniones que tuvimos, juan andrés me comentó su idea principal de no trabajar con TADs, pero luego de hablarlo con gerardo nos comentó que la mejor opción era que lo hiciesemos, sobretodo porque solamente con structs no estaríamos implementando lo que aprendimos en EDD, por lo tanto, decidimos modificarlo

## Tercera Semana

- Todo el fin de semana juan andrés y yo hemos estado en llamada revisando las cosas que podemos hacer, hemos dedicido que crearemos un TAD monopoly el cual tratará el juego principal, esto porque partida solo trata turno por turno, el TAD monopoly lo hará para toda la partida como tal, por lo que haremos será tener la función del retroceso dentro de este.

- Para el martes creamos las formas para poder generar las acciones que deben de suceder cuando un jugador cae en cierta casilla, como el comprar, vender, rentar, hipotecar propiedades, etc...


---
## Pre y pos condiciones de funciones:

### Cartas:

- **CartaArcaComunal**:
    - CrearCartaArcaComunal: string x string x string -> CartaArcaComunal

        - pre: Ninguna

        - pos: La función devuelve una nueva instancia de CartaArcaComunal (cac) cuyos miembros tipo, nombre, y mensaje son idénticos a los valores de los argumentos de entrada.

    - GenerarColaCartasArcaComunal: -> queue< CartaArcaComunal >

        - pre:
            - **Archivo Existente**: Debe existir un archivo llamado `viernes13/CartasArcaComunal.json` en una ruta accesible.

            - **Formato Valido**:  El archivo JSON debe ser un *array* de objetos (`j.size()` es válido) y cada objeto debe contener las claves `"tipo"`, `"nombre"` y `"mensaje"` para que la función `CrearCartaArcaComunal` se ejecute sin errores de acceso.

            - **Permisos:** El proceso debe tener permisos para abrir y leer el archivo.

        - pos:
            - **Éxito:** La función devuelve una `std::queue<CartaArcaComunal>` que contiene todas las cartas leídas del archivo JSON.
            - **Orden:** El orden de las cartas en la cola está **aleatorizado** (`std::shuffle`) con respecto al orden en que aparecían en el archivo JSON.
            - **Fallo:** Si el archivo no se abre correctamente, la función lanza una excepción de tipo `std::runtime_error`.

- **CartaSuerte**:
    - CrearCartaSuerte: string x string x string -> CartaSuerte
        
        - pre: Ninguna explícita.
        - pos: La función devuelve una nueva instancia de CartaSuerte (`cs`) cuyos miembros `nombre`, `tipo`, y `mensaje` son idénticos a los valores de los argumentos de entrada.

    - GenerarColaCartasSuerte: -> queue< CartaSuerte >
        
        - pre: 
            - **Archivo Existente**: Debe existir un archivo llamado **`viernes13/CartasSuerte.json`** en una ruta accesible.
            - **Formato Válido**: El archivo JSON debe ser un *array* de objetos (`j.size()` es válido) y cada objeto debe contener las claves **`"nombre"`, `"tipo"` y `"mensaje"`** para que la función `CrearCartaSuerte` se ejecute sin errores de acceso.
            - **Permisos:** El proceso debe tener permisos para abrir y leer el archivo.
        - pos:
            - **Éxito:** La función devuelve una `std::queue<CartaSuerte>` que contiene todas las cartas leídas del archivo JSON.
            - **Orden:** El orden de las cartas en la cola está **aleatorizado** (`std::shuffle`) con respecto al orden en que aparecían en el archivo JSON.
            - **Fallo:** Si el archivo no se abre correctamente, la función lanza una excepción de tipo `std::runtime_error`.

### Casillas:

- **Carcel**:
    - CrearCarcel: -> Carcel
        - pre: Ninguna

        - pos: Devuelve una nueva instancia de `Carcel` con el contenedor prisioneros inicializado y vacío.

    - Arresta: Carcel x User -> void
        - pre: El puntero user no debe ser nulo (`nullptr`).
        - pos: El usuario apuntado por user se añade al mapa `carcel.prisioneros` utilizando su `user->nombre` como clave. La cuenta de turnos de ese usuario en prisión se inicializa a 0. 

    - LiberarDeLaCarcel: Carcel x string -> void
        - pre: El nombre de usuario debe existir como clave en el mapa `carcel.prisioneros`. (Si no existe, la función erase no hace nada, pero la precondición lógica es que el usuario esté encarcelado).
        - pos: La entrada correspondiente al nombre es eliminada del mapa `carcel.prisioneros`, liberando al usuario de la cárcel dentro del registro de la partida.
    
    - AumentarTurnos: Carcel x string -> void
        - pre: El nombre de usuario debe existir como clave en el mapa carcel.prisioneros.
        - pos: El contador de turnos (`second`) asociado al usuario en `carcel.prisioneros[nombre]` se incrementa en uno.
    
    - EstaArrestado: Carcel x string -> bool
        - pre: Ninguna
        - pos: La función devuelve true si el nombre existe como clave en el mapa carcel.prisioneros; de lo contrario, devuelve false. El estado de la carcel (que es const) no se modifica.

- ***Casilla***:
    - CrearCasilla: string x int -> Casilla
        - pre: Ninguna
        - pos: La función devuelve una nueva instancia de Casilla (c) con los siguientes estados:
            * El miembro `c.tipo` es inicializado con el valor de `_tipo`.
            * El miembro `c.indiceTipo` es inicializado con el valor de `_indiceTipo`.

- **Ferrocarril**:
    - CrearFerrocarril: string x int x bool x int[4] -> Ferrocarril
        - pre: El array _alquiler debe ser un array de enteros de tamaño 4, conteniendo los valores de renta para 1, 2, 3 y 4 ferrocarriles, respectivamente.
        - pos: La función devuelve una nueva instancia de `Ferrocarril` con los siguientes estados:
            * El miembro tipo se establece estáticamente a `Ferrocarril`.
            * Los miembros nombre, valor, hipotecada se inicializan con los valores de los argumentos de entrada.
            * El array alquiler es una copia de los valores proporcionados en `_alquiler`.

    - ValorRentaFerrocarril: int -> int
        - pre: El argumento `nFerro` (número de ferrocarriles poseídos) debe ser un entero entre 1 y 4 (ambos inclusive).
        - pos:
            * **Exito**: La función devuelve el valor entero de la renta a pagar, calculado mediante la fórmula exponencial: $25 \cdot 2^{nFerro - 1}$.
            * **Fracaso**: Si nFerro está fuera del rango [1, 4], la función lanza una excepción de tipo `std::invalid_argument`.

- **Propiedad**:
    - CrearPropiedad: string x string x string x bool x int x int[6] x int x int x int x int -> Propiedad
        - pre: El array `_alquiler` debe ser de tamaño 6, conteniendo los valores de renta desde 0 casas hasta 1 hotel.
        - pos: Devuelve una nueva instancia de Propiedad con los siguientes estados:
            * El miembro tipo se establece estáticamente a `Propiedad`.
            * Los miembros se inicializan con los valores de los argumentos de entrada.
            * Los miembros `numCasas` y `numHoteles` se inicializan a 0.
    
    - ConstruirNCasas: Propiedad x int -> Propiedad
        - pre:
            * El total de casas después de la construcción (prop.numCasas + casas) no debe superar 4.
            * La propiedad no debe poseer ya un hotel (`prop.numHoteles == 0`).
        - pos:
            * **Exito**: Devuelve una nueva instancia de Propiedad (por valor) donde prop.numCasas se ha incrementado en la cantidad casas.
            * **Fallo**: Si no se cumple alguna precondición, la función lanza una excepción de tipo std::invalid_argument.

    - ConsturirHotel: Propiedad -> Propieda
        - pre: La propiedad debe tener exactamente 4 casas construidas (`prop.numCasas == 4`).
        - pos:
            * **Exito**: Devuelve una nueva instancia de Propiedad (por valor) donde:
                * El miembro `prop.numCasas` se establece a 0.
                * El miembro `prop.numHoteles` se establece a 1.
            * **Fallo**: Si la propiedad no tiene 4 casas, la función lanza una excepción de tipo `std::invalid_argument`.
    
    - ValorRentaPropiedad: Propiedad x bool -> int
        - pre: Ninguna
        - pos: La función devuelve un valor de renta entero, basado en las siguientes reglas:
            * Si monopolio es false, devuelve la renta base (sin casas) de la propiedad: `prop.alquiler[0]`.
            * Si monopolio es true y `prop.numCasas == 0` y `prop.numHoteles == 0`, devuelve el doble de la renta base: `2 * prop.alquiler[0]`.
            * Si monopolio es true y `prop.numCasas` es entre 1 y 4, devuelve el valor de alquiler correspondiente a esa cantidad de casas: `prop.alquiler[prop.numCasas]`.
            * Si monopolio es true y `prop.numHoteles == 1`, devuelve el valor de alquiler del hotel: `prop.alquiler[5]`.
            * Si ninguna condición anterior se cumple (lo cual, dado el código, solo puede significar que numCasas o numHoteles son valores inesperados), devuelve 0.

- **Servicio**:
    - CrearServicio: string x int x int -> Servicio
        - pre: Ninguna
        - pos: Devuelve una nueva instancia de Servicio con los siguientes estados:
            * El miembro tipo se establece estáticamente a `Servicio`.
            * Los miembros `nombre`, `valor` e `hipoteca` se inicializan con los valores de los argumentos de entrada.

    - ValorRentaServicio: int x int -> int
        - pre: El argumento `tirada` debe ser un entero que representa la suma de los dados lanzados y el argumento `nServicios` (número de Servicios Públicos poseídos por el dueño) debe ser 1 o 2.
        - pos: La función devuelve un valor de renta entero, basado en la cantidad de servicios poseídos:
            * Si `nServicios` es 1, la renta es 4 veces la tirada de dados.
            * Si `nServicios` es 2, la renta es 10 veces la tirada de dados.
            * En cualquier otro caso (como 0), devuelve 0.

    - MultDadoServicio: int -> int:
        - pre: El argumento `ns` (número de servicios poseídos) debe ser un entero entre 0 y 2 (ambos inclusive).
        - pos: La función devuelve el multiplicador entero correspondiente a la cantidad de servicios poseídos:
            * Si `ns` es 0, devuelve 1 (lo cual sugiere una inicialización o un estado no-monopolio atípico).
            * Si `ns` es 1, devuelve 4.
            * Si `ns` es 2, devuelve 10.
            * **Fallo**: Si `ns` está fuera del rango [0, 2], la función lanza una excepción de tipo `std::invalid_argument`.

### General

- **ArcaComunal**:
    - IniciarArcaComunal: -> ArcaComunal
        - pre:
            * Debe existir un archivo llamado viernes13/CartasArcaComunal.json en una ruta accesible.
            * El archivo JSON debe ser un array de objetos y cada objeto debe contener las claves necesarias (`tipo`, `nombre`, `mensaje`) para que la función `CrearCartaArcaComunal` se ejecute sin errores.
        - pos: 
            * **Exito**: Devuelve una nueva instancia de `ArcaComunal` (`ac`) cuya `colaCartas` contiene todas las cartas leídas del JSON y la cola de cartas (`ac.colaCartas`) se ha llenado con las cartas en un orden aleatorizado (`std::shuffle`).
            * **Fallo**: Si el archivo no se abre correctamente (`archivo.is_open()` es falso), la función lanza una excepción de tipo `std::runtime_error`.
    
    - SacarCartaArcaComunal: ArcaComunal -> CartaArcaComunal
        - pre: La cola de cartas del Arca Comunal (`ac.colaCartas`) no debe estar vacía.
        - pos: La función devuelve la primera carta (front()) de la cola y la carta que se acaba de extraer se mueve del frente de la cola a la parte posterior de la misma. El tamaño total del mazo no cambia.

- **Banco**:
    - crearBanco: std::vector< Propiedad > -> Banco
        - Ninguna explícita. El vector `_propiedades` debe contener objetos Propiedad válidos.
        -  La función devuelve una nueva instancia de `Banco` (`b`):
            * * El miembro `b.propiedades` es inicializado con una copia de los objetos Propiedad pasados en el vector `_propiedades`. Estos son los activos de la banca disponibles para la compra inicial por parte de los jugadores.

- **Partida**:

    - TirarDado: Null -> int
        - Pre: Nada.
        - Pos: la función devuelve un número entero randomizado entre `1` y `6`.

    - DecidirOrdenUsuarios: Partida -> void
        - Pre: `p.usuarios` debe ser un `map<string, User>` con al menos un jugador.
               Cada usuario debe tener un `nombre`, una `posición` y un `contador de pares` válido.
        - Pos: Se define el orden de todos los usuarios según la suma de sus dados.
               Como usamos la `posición` temporalmente para ordenar, se limpia al finalizar.
               Como es `void`, se modifica `p` directamente.

    - IniciarPartida: vector<User> -> Partida
        - Pre: `listaUsuarios` debe contener al menos un elemento.
               Deben existir `crearTablero()` y `CrearCarcel()`.
        - Pos: se crea una partida `p` con:
                - `p.nTurno = 0`
                - `p.tablero = crearTablero()`
                - `p.carcel = CrearCarcel()`
                - `p.usuarios` usando el `nombre` como clave.
               No modifica `listaUsuarios` original.

    - PropiedadPerteneceAAlguien: Partida x string -> bool
        - Pre: `p.usuarios` y `nombrePropiedad` deben existir y ser válidos.
        - Pos: `true` si algún usuario posee la propiedad, `false` si nadie la tiene.

    - DuenoDeLaPropiedad: Partida x string -> string
        - Pre: `p.usuarios` y `nombrePropiedad` deben existir y ser válidos.
        - Pos: retorna el nombre del dueño o `"nadie"` si no hay dueño.

    - GanarPropiedad: Partida x User x Propiedad -> Partida
        - Pre: `u.nombre` debe existir como clave en `p.usuarios`.
        - Pos: la propiedad se agrega a `p.usuarios[u.nombre].propiedades`.
               Se retorna la partida modificada.

    - AvanzarJugador: Partida x User -> void
        - Pre: `jugador.posicion` debe estar entre `0` y `39`.
               `jugador` debe existir dentro de `p.usuarios`.
               `p.tablero` debe ser válido.
        - Pos: el jugador avanza según los dados.
               Si pasa por la casilla de salida recibe dinero.
               Si saca `3` pares o cae en `"Ir a la cárcel"`, se envía a la cárcel.
               Se ejecuta la acción de la casilla correspondiente.
               Se modifica tanto `p` como `jugador`.

    - ReglaTercerTurnoCarcel: Carcel x string -> void
        - Pre: `nombreJugador` debe existir dentro de `carcel.prisioneros`.
        - Pos: se incrementa `turnosEnCarcel`.
               Si llega a `3`, se libera al jugador y se ubica en la casilla `10`.

    - ReglaTercerParFuera: Carcel x User -> void
        - Pre: `user.contPares` debe tener el conteo correcto.
        - Pos: si `user.contPares == 3`, el jugador va a la cárcel.
               Si no, no ocurre nada.

    - NumeroDePropiedades: Partida x string -> int
        - Pre: `nombreJugador` debe existir en `p.usuarios`.
        - Pos: retorna el tamaño de `p.usuarios[nombreJugador].propiedades`.

    - NumeroDeServicios: Partida x string -> int
        - Pre: `nombreJugador` debe existir en `p.usuarios`.
        - Pos: retorna el tamaño de `p.usuarios[nombreJugador].servicios`.

    - NumeroDeFerrocarriles: Partida x string -> int
        - Pre: `nombreJugador` debe existir en `p.usuarios`.
        - Pos: retorna el tamaño de `p.usuarios[nombreJugador].ferrocarriles`.

    - PropietarioDeServicio: Partida x string -> string
        - Pre: `nomServicio` debe existir en el tablero.
        - Pos: retorna el nombre del dueño o `"except"` si nadie lo posee.

    - PropietarioDeFerrocarril: Partida x string -> string
        - Pre: `nomFerrocarril` válido.
        - Pos: retorna el dueño o `"except"`.

    - PropietarioDePropiedad: Partida x string -> string
        - Pre: `nomPropiedad` válido.
        - Pos: retorna el dueño o `"except"`.

    - PropiedadEnMonopolio: Partida x string -> bool
        - Pre: `nomPropiedad` debe existir en `p.tablero`.
        - Pos: `true` si el jugador del turno tiene todas las propiedades
               del mismo `color`. `false` si no.

    - PuedeComprar: User x int -> bool
        - Pre: `precio` debe ser mayor o igual a `0`.
        - Pos: `true` si `user.cash >= precio`, de lo contrario `false`.

    - NormalizarRespuesta: string -> string
        - Pre: la entrada debe ser válida.
        - Pos: retorna la cadena convertida a minúsculas.

    - EjecutarCasilla: Partida x User x int -> void
        - Pre: `user.posicion` entre `0` y `39`.
               `p.tablero` correcto.
        - Pos: ejecuta la acción correspondiente de la casilla:
                compra, renta, subasta, o acción especial.
               Modifica `p` y al `user`.

    - EjecutarCasillaEspecial: Partida x User x string -> void
        - Pre: `nombreCasilla` debe ser una casilla especial válida.
        - Pos: aplica el efecto: pagar impuestos, moverse, cárcel, etc.
               Modifica la partida y/o al usuario.

    - EjecutarArcaComunal: Partida x User -> void
        - Pre: debe existir al menos una carta en `p.arcaComunal`.
        - Pos: aplica el efecto de la carta: dinero, movimiento, cárcel, etc.
               Modifica al jugador y/o a la partida.

    - SubastarPropiedad: Partida x string x string -> void
        - Pre: `nomCasilla` válida dentro del tablero.
               Deben existir al menos 2 jugadores.
        - Pos: se realiza una subasta.
               El ganador paga y recibe la propiedad.
               Se modifica `p`.

    - AsignarPropiedad: Partida x string x string -> void
        - Pre: `nomCasilla` válida.
               `comprador` existe en `p.usuarios`.
        - Pos: la propiedad se agrega a `p.usuarios[comprador]`.
               Se descuenta el costo correspondiente.


- **Monopoly**:

    - mostrarMenuPrincipal: -> void
        - Pre: ninguna. El objeto `Monopoly` debe estar correctamente construido.
        - Pos: muestra el menú principal y permite al usuario seleccionar opciones.
               Llama a otras funciones como `iniciarNuevaPartida()`, `jugarTurno()`, etc.
               No modifica el estado salvo a través de las operaciones seleccionadas.

    - iniciarNuevaPartida: -> void
        - Pre: deben existir las funciones `CrearUsuario()`, `IniciarPartida()` y `DecidirOrdenUsuarios()`.
        - Pos: inicializa `partidaActual` con 4 jugadores ingresados por consola.
               Limpia el historial `partidas`.
               Deja `juegoIniciado = true`.

    - mostrarEstadoPartida: -> void
        - Pre: `juegoIniciado == true`.
        - Pos: imprime el estado actual de la partida:
               turno, dinero de cada jugador, propiedades, servicios y ferrocarriles.
               No modifica datos.

    - jugarTurno: -> void
        - Pre: `juegoIniciado == true`.
               `partidaActual.ordenUsuarios` no debe estar vacío.
        - Pos: guarda el estado anterior mediante `GuardarEstadoPartida()`.
               Ejecuta el turno del jugador actual usando `AvanzarJugador()`.
               Actualiza `p.nTurno` al siguiente jugador.
               Modifica `partidaActual`.

    - DevolverPartida: -> void
        - Pre: la pila `partidas` debe tener al menos un elemento.
        - Pos: restaura `partidaActual` al estado previamente guardado.
               Reduce la pila `partidas` en un elemento.
               Permite deshacer el turno anterior.

    - GuardarEstadoPartida: -> void
        - Pre: `juegoIniciado == true`.
        - Pos: guarda una copia completa de `partidaActual` en la pila `partidas`.

    - VerHistorial: -> void
        - Pre: ninguna.
        - Pos: muestra cuántos estados hay en `partidas`.
               No modifica el estado.

    - MenuPropiedades: -> void
        - Pre: `juegoIniciado == true`.
               `partidaActual.nTurno` debe ser válido.
        - Pos: presenta un menú para manejar propiedades del jugador actual.
               Según la acción elegida, puede modificar:
                    - `prop.numCasas`
                    - `prop.numHoteles`
                    - `prop.hipotecada`
                    - `user.cash`
               Permite construir, vender, hipotecar y deshipotecar.

    - MostrarPropiedadesJugador: string -> void
        - Pre: `jugador` debe existir en `partidaActual.usuarios`.
        - Pos: lista todas las propiedades detalladas del jugador.
               No modifica la partida.

    - ComprarCasa: string x string -> bool
        - Pre: `juegoIniciado == true`.
               `jugador` debe existir.
               `nombreProp` debe ser propiedad del jugador.
               `PuedeConstruirCasa()` debe devolver true.
               `user.cash >= prop.valorCasa`.
        - Pos: añade una casa (`prop.numCasas++`).
               Se descuenta `prop.valorCasa` de `user.cash`.
               Guarda estado previo para deshacer.
               Retorna true si se construyó.

    - ComprarHotel: string x string -> bool
        - Pre: `juegoIniciado == true`.
               `PuedeConstruirHotel()` debe devolver true.
        - Pos: `prop.numHoteles = 1`, `prop.numCasas = 0`.
               Se descuenta `prop.valorHotel` de `user.cash`.
               Guarda estado previo.
               Retorna true si se construyó.

    - VenderCasa: string x string -> bool
        - Pre: `juegoIniciado == true`.
               `prop.numCasas > 0`.
               No puede romper el equilibrio entre propiedades del mismo color.
        - Pos: `prop.numCasas--`.
               Se suma a `user.cash` la mitad de `prop.valorCasa`.
               Guarda estado previo.
               Retorna true si se vendió.

    - VenderHotel: string x string -> bool
        - Pre: `prop.numHoteles == 1`.
        - Pos: `prop.numHoteles = 0`.
               `prop.numCasas = 4` (regla oficial).
               `user.cash += prop.valorHotel / 2`.
               Guarda estado previo.
               Retorna true si se vendió.

    - HipotecarPropiedad: string x string -> bool
        - Pre: `prop.hipotecada == false`.
               `prop.numCasas == 0` y `prop.numHoteles == 0`.
        - Pos: `prop.hipotecada = true`.
               `user.cash += prop.valorHipotecar`.
               Guarda estado previo.
               Retorna true si se hipotecó.

    - DeshipotecarPropiedad: string x string -> bool
        - Pre: `prop.hipotecada == true`.
               `user.cash >= prop.valorDesHipotecar`.
        - Pos: `prop.hipotecada = false`.
               `user.cash -= prop.valorDesHipotecar`.
               Guarda estado previo.
               Retorna true si se deshipotecó.

    - ObtenerPropsColor: Partida x string x string -> vector<Propiedad*>
        - Pre: `jugador` existe en `p.usuarios`.
        - Pos: retorna un vector de punteros a las propiedades de ese color que posee el jugador.
               No modifica la partida.

    - TieneMonopolio: Partida x string x string -> bool
        - Pre: `color` debe existir en el tablero.
               `jugador` debe existir en `p.usuarios`.
        - Pos: retorna true si el jugador posee todas las propiedades de ese color.
               No modifica nada.

    - PuedeConstruirCasa: Partida x string x Propiedad -> bool
        - Pre: propiedad debe pertenecere a `jugador`.
        - Pos: retorna true si:
                - no está hipotecada
                - no tiene hotel
                - `TieneMonopolio == true`
                - respeta el equilibrio de casas
                - `prop.numCasas < 4`
               No modifica estado.

    - PuedeConstruirHotel: Partida x string x Propiedad -> bool
        - Pre: propiedad debe pertenecer a `jugador`.
        - Pos: retorna true si:
                - no está hipotecada
                - `TieneMonopolio == true`
                - `prop.numCasas == 4`
                - `prop.numHoteles == 0`
                - todas las propiedades del color tienen 4 casas
               No modifica estado.


- **Tablero**: 
    - CrearTablero: -> Tablero
        - pre: 
            * Deben existir y ser accesibles los siguientes archivos en la ruta viernes13/: `Propiedades.json`, `Ferrocarriles.json`, `Servicios.json`, `CasillasEspeciales.json`, y `Casillas.json`.
            * Todos los archivos JSON deben contener un array de objetos y tener las claves requeridas para la inicialización (nombre, valor, alquiler, etc.) y la llamada a sus respectivas funciones CrearX.
            * Los datos en `Casillas.json` deben contener los valores de tipo y posicion que corresponden al índice de los objetos creados en los otros vectores (ferrocarriles, propiedades, etc.).
        - pos:
            * **Exito**: Devuelve una nueva instancia de Tablero con sus cinco vectores (casillas, ferrocarriles, propiedades, servicios, especiales) poblados con los datos leídos y estructurados a partir de los archivos JSON.
            *  **Fallo**: Si cualquier archivo JSON falla al abrirse (`!archivo.is_open()`), la función lanza una excepción de tipo `std::runtime_error` con un mensaje que indica el archivo problemático. 

    - ObtenerCasilla: -> Tablero x int -> Casilla
        - pre: El vector `tablero.casillas` no debe estar vacío.
        - pos: La función devuelve el objeto Casilla que se encuentra en la posición efectiva del tablero, apra ello se utiliza el operador módulo para manejar el movimiento circular alrededor del tablero: `pos % tablero.casillas.size()`.

- **User**: 
    - CrearUsuario: string -> User
        - pre: Ninguna
        - pos: Devuelve una nueva instancia de User con el siguiente estado inicial:
        * `nombre = _name`
        * `cash = 1500`
        * `posicion = 0`
        * `contPares = 0`
        * `activo = true`
        * `cartaSalirDeLaCarcel = false`
        * Los vectores de inventario (`servicios`, `propiedades`, `ferrocarriles`) están vacíos.
    
    - CambiarNombreUsuario: User x string -> User
        - pre: Ninguna
        - pos: Devuelve una copia de `user` donde el miembro nombre ha sido actualizado al valor de `newName`.

    - AumentarPosicion: User x int -> User
        - pre: El argumento `aumento` debe ser un entero no negativo (representando el movimiento de las casillas).
        - pos: Devuelve una copia de `user` donde el miembro posicion ha sido incrementado en el valor de `aumento`.

    - GanarDinero: User x int -> User
        - pre: El argumento `dinero` debe ser un entero no negativo.
        - pos: Devuelve una copia de `user` donde el miembro `cash` ha sido incrementado en la cantidad de `dinero`.

    - PerderDinero: User x int -> User
        - pre: El argumento `dinero` debe ser un entero no negativo.
        - pos: Devuelve una copia de `user` donde el miembro `cash` ha sido decrementado en la cantidad de `dinero`.

    - UsuarioEliminado: User -> User
        - pre: Ninguna.
        - pos: Devuelve una copia de `user` donde el miembro `activo` se establece a `false`.

    - ResetContPares: User -> User
        - pre: Ninguna.
        - pos: Devuelve una copia de `user` donde el miembro `contPares` se establece a `0`.

    - AumentarContPares: User -> User
        - pre: Ninguna.
        - pos: Devuelve una copia de `user` donde el miembro `contPares` se ha incrementado en `1`.

    - GanarCartaSalirDeLaCarcel: User -> User
        - pre: Ninguna.
        - pos: Devuelve una copia de `user` donde el miembro `cartaSalirDeLaCarcel` se establece a `true`.

    - GastarCartaSalirDeLaCarcel: User -> User
        - pre: Ninguna.
        - pos: Devuelve una copia de `user` donde el miembro `cartaSalirDeLaCarcel` se establece a `false`.