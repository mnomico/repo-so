# World Wide Web y HTTP

## World Wide Web (WWW)

La **World Wide Web (WWW)** es un sistema de información distribuido a nivel global. Funciona con una arquitectura cliente-servidor, donde el cliente solicita documentos, y el servidor almacena y entrega esos documentos.

**Tipos de páginas Web:**
- Página simple: todo el contenido se obtiene en una única transacción HTTP.
- Página compuesta: contiene enlaces a otras páginas. Necesita más de una transacción HTTP.

**Cliente Web (Navegador)**
Un navegador está formado por:
- Controlador: maneja la entrada del usuario.
- Protocolos cliente: HTTP, FTP, TELNET, SMTP.
- Intérpretes: para HTML, Java, JavaScript, etc.

**Servidor Web**
- Guarda y entrega los documentos.
- Puede usar caché en memoria para acelerar el acceso.
- Puede procesar múltiples solicitudes usando multihilo o multiproceso.

**URI** significa Uniform Resource Identifier (Identificador Uniforme de Recursos). Es una cadena de texto que identifica un recurso (documento, imagen, servicio, etc.) en Internet. Puede incluir o no una dirección completa.

Hay dos tipos principales:
- **URL**: Localizador (incluye ubicación)
- **URN**: Nombre único sin ubicación directa. Ej: urn:isbn:0451450523

Una URL define cómo localizar un documento en la Web. Su formato es el siguiente:

``` protocolo://host:puerto/ruta ```

**Documentos estáticos (Static Documents)**
- Son archivos almacenados en disco que se entregan tal como están.
- Son los más simples y comunes.
- Normalmente están escritos en HTML puro.

**Documentos dinámicos (Dynamic Documents)**
- Son documentos que se crean en el momento en que el cliente los solicita.
- El servidor ejecuta un programa en tiempo real (por ejemplo, un script PHP o Python).
- El programa genera una respuesta basada en:
    - Parámetros enviados por el cliente
    - Condiciones actuales del servidor o base de datos
- Son útiles para sitios personalizados, formularios, acceso a base de datos, etc.

**Documentos activos (Active Documents)**
- Son documentos que permanecen activos después de ser entregados al cliente.
- Pueden interactuar con el usuario o recibir datos del servidor en tiempo real.
- Requieren un entorno de ejecución en el lado del cliente.
- Ej: juego, chat, etc.

## HTTP (Hypertext Transfer Protocol)

HTTP es el protocolo utilizado para la comunicación entre el cliente y el servidor Web. Es un protocolo de comunicación orientado a transacciones cliente-servidor, sin estado (stateless) y basado en texto.

Utiliza un modelo de transacción, que se compone de una solicitud (request) enviada por el cliente, y de una respuesta (response) generada por el servidor.

Una **solicitud HTTP** contiene:
- Línea de solicitud (request line)
- Cabeceras (headers)
- (Opcionalmente) un cuerpo (body)

Formato de una solicitud HTTP:

``` método URI versión ```

- Método: Acción solicitada (GET, POST, HEAD, etc.)
- URI: Ruta del recurso solicitado
- Versión: Versión de HTTP (1.0, 1.1, 2.0...)

**Métodos comunes**
- GET: Solicita un recurso (el más común)
- POST: Envía datos al servidor (por ejemplo, desde un formulario)
- HEAD: Solicita solo las cabeceras, no el cuerpo
- PUT: Carga un archivo al servidor
- DELETE: Elimina un recurso
- OPTIONS: Consulta sobre capacidades del servidor para un recurso específico

**Cabeceras de solicitud (Request Headers)**
Indican información adicional como el servidor destino, información del cliente y tipo de contenido que acepta el navegador.

Una **respuesta HTTP** contiene:
- Línea de estado (status line)
- Cabeceras de respuesta (headers)
- Cuerpo del mensaje (contenido solicitado): Contiene el documento solicitado, como HTML, imagen, video, etc.

Formato de una respuesta HTTP:

``` versión código estado ```

**Códigos y estados**
- 200 OK: respuesta exitosa
- 301 Moved Permanently: redirección
- 400 Bad Request: solicitud malformada
- 404 Not Found: archivo no encontrado
- 500 Internal Server Error: error del servidor

**Conexiones persistentes vs no persistentes**

HTTP se basa en TCP como protocolo de transporte.

En HTTP **no persistente**, se abre una nueva conexión TCP para cada objeto.
Después de enviar la respuesta, la conexión se cierra inmediatamente.

Los problemas de este tipo de conexión son los siguientes:
- Aumenta el tiempo de conexión (establecer TCP es costoso).
- Congestiona en la red.
- No es eficiente cuando una página requiere múltiples objetos.

HTTP/1.0 usaba este tipo de conexión por defecto.

En HTTP **persistente**, la conexión TCP permanece abierta después de transferir el primer objeto. Se pueden enviar múltiples solicitudes/respuestas por la misma conexión.

Esto introduce algunas ventajas:
- Menor número de conexiones TCP abiertas.
- Mejora el rendimiento.
- Reduce la carga sobre el servidor y la red.

HTTP/1.1 usa conexiones persistentes por defecto.

Para cerrar la conexión, el cliente debe enviar Connection: close.

HTTP es un protocolo sin estado: El servidor no recuerda nada entre una solicitud y la siguiente. 
Para solucionar esto, se introdujo el concepto de cookie.

Una **cookie** es un archivo de texto que el servidor almacena en el navegador del cliente. Se utiliza para identificar al usuario entre solicitudes. Permite mantener sesiones, preferencias, carritos de compra, etc.

**Funcionamiento de cookies**

El servidor crea una cookie. Cuando el cliente accede a una página por primera vez, el servidor puede crear una cookie que contiene un identificador único, una fecha de expiración y la ruta donde la cookie será válida.

Luego el navegador almacena la cookie, y cada vez que el usuario haga una solicitud sobre esa ruta, el navegador agrega la cookie en la cabecera.

Las cookies son esenciales para:
- Autenticación de usuarios: permiten identificar al usuario en múltiples solicitudes y mantener la sesión activa.
- Personalización de sitios
- Seguimiento de actividad

**Servidores Proxy (Proxy Servers)**
Un servidor proxy es un intermediario entre el cliente y el servidor.

Cuando un cliente hace una solicitud HTTP, en lugar de enviarla directamente al servidor destino, la envía al proxy.
El proxy decide hacer lo siguiente:
- Si tiene una copia en caché del recurso, se la devuelve al cliente.
- Si no la tiene, reenvía la solicitud al servidor, guarda una copia del recurso, y se la entrega al cliente.

**Ventajas del uso de proxies**
- Aceleración: Si el proxy tiene el contenido en caché, lo entrega más rápido.
- Reducción de tráfico: Evita múltiples solicitudes al mismo recurso desde distintos clientes.
- Seguridad: Oculta la identidad y ubicación del cliente.
- Filtrado de contenido: Puede bloquear o permitir sitios según políticas.
- Balance de carga: Puede distribuir solicitudes entre varios servidores backend.

**Tipos de proxies**
- Directo: El cliente envía las solicitudes directamente al servidor (no conoce al proxy).
- Proxy normal: El cliente sabe que está usando un proxy y le envía todas las solicitudes.
- Proxy inverso: El proxy está del lado del servidor, recibe solicitudes y las distribuye internamente.

## Ejemplo de Transacción HTTP

1. Un usuario escribe en su navegador: http://www.ejemplo.com/index.html
2. Se establece una conexión TCP entre cliente y servidor. El navegador (cliente) realiza una solicitud HTTP para obtener esa página.

```
GET /index.html HTTP/1.1    # indica que el cliente quiere leer el recurso /index.html
Host: www.ejemplo.com       # especifica el servidor (requerido en HTTP/1.1)
User-Agent: Mozilla/5.0     # identifica el navegador
Accept: text/html           # indica que el cliente acepta documentos HTML
```

3. Respuesta del servidor (HTTP Response)

```
HTTP/1.1 200 OK                         # indica que la solicitud fue exitosa
Date: Sun, 01 Jun 2025 12:00:00 GMT
Server: Apache/2.4.54
Content-Type: text/html
Content-Length: 612
                                        # contenido HTML
<html>
<head><title>Ejemplo</title></head>
<body>
<h1>Bienvenido a Ejemplo.com</h1>
</body>
</html>
```

**HTML (HyperText Markup Language)** es el lenguaje de marcado que los navegadores utilizan para interpretar y mostrar páginas web. 
- Describe la estructura y semántica del contenido.
- Utiliza etiquetas para definir partes del documento. 
- La estructura que define se representa en el DOM (Document Object Model).

La **Common Gateway Interface (CGI)** es un estándar que permite al servidor web ejecutar programas externos para generar contenido dinámico.

Cuando el servidor recibe una petición a un recurso CGI:
- Le pasa variables de entorno (como método, encabezados, etc.).
- Envía datos POST a través de stdin.
- El script responde mediante stdout con encabezados HTTP y el cuerpo de la respuesta.

Las formas principales en las que un programa puede recibir parámetros por medio de la interfaz CGI son:
- A través de la cadena de consulta (GET - QUERY_STRING): Los parámetros se incluyen en la URL. El servidor los guarda en la variable de entorno QUERY_STRING.
- Mediante entrada estándar (POST): Los datos viajan en el cuerpo de la petición. El servidor los pasa por stdin y define CONTENT_LENGTH y CONTENT_TYPE.
- Mediante PATH_INFO y SCRIPT_NAME: Permite incluir parámetros en la ruta. SCRIPT_NAME contiene el nombre del script y PATH_INFO la información extra.

---

# Cableado estructurado

---

# Capa de Red y Protocolo IP

Para resolver el problema de la variedad de tecnologías heterogéneas, se necesita una capa de red que permita que todos los dispositivos se comuniquen bajo un esquema común, sin importar el tipo de enlace físico que utilicen.

Para esto se crea una red “virtual” con un esquema de direccionamiento y de nombres propio, ruteo, mantenimiento de la información de estado, y contabilidad y gestión de las congestiones.

La capa de red proporciona esta funcionalidad mediante el uso del **Protocolo IP (Internet Protocol)**. IP ofrece una forma estándar de direccionar y enrutar los datos a través de diferentes redes. 

Todos los dispositivos que participan en una red IP comparten al menos dos o tres características comunes, como el esquema de direccionamiento (IP), el formato del paquete, y las reglas para el encaminamiento.

La capa de red se encarga de enrutar los paquetes a través de múltiples saltos, desde el origen hasta el destino, aunque se encuentren en diferentes redes físicas.

Para lograr esto, la capa de red debe implementar:
- Estrategias de selección de ruta (ruteo) para determinar el mejor camino.
- Técnicas de conmutación de nivel 3, que permiten el reenvío eficiente de los paquetes entre diferentes nodos de la red.

**Diferencias entre el envío de mensajes (PDU) en la capa 3 (red) y tramas en la capa 2 (enlace de datos)**
La capa de enlace se encarga de la comunicación entre nodos directamente conectados dentro de una misma red local (LAN). La unidad de datos que maneja se llama trama, y en ella se utilizan direcciones físicas (MAC) para identificar al emisor y al receptor.

La capa de red permite la comunicación entre diferentes redes, utilizando paquetes IP como unidades de datos. En esta capa se usan direcciones lógicas (IP), que se mantienen iguales desde el origen hasta el destino final. Los routers utilizan estas direcciones para decidir cómo reenviar los paquetes.

## Conmutación

Una red conmutada consta de una serie de nodos interconectados, denominados conmutadores. Los conmutadores son dispositivos capaces de crear  conexiones temporales entre dos o más dispositivos enlazados al conmutador. En una red conmutada, algunos de estos nodos se conectan a sistemas finales, otros se utilizan solo para encaminamiento.

En el ámbito de una red de datos, conmutación se refiere al proceso de dirigir unidades de información desde un origen hacia un destino a través de una red, eligiendo el camino adecuado entre múltiples posibles.

### Conmutación de circuitos

Consta de un conjunto de conmutadores conectados por enlaces físicos. Una conexión entre dos estaciones es un camino dedicado formado por uno o más enlaces. Cada conexión sólo utiliza un canal dedicado en cada enlace, y cada enlace se divide en n canales utilizando FDM o TDM.

Los sistemas finales se conectan directamente al conmutador. Cuando el sistema A necesita comunicarse con otro sistema, el sistema A tiene que solicitar una conexión que sea aceptada por todos los conmutadores así como por el sistema destino. 

Esta fase se denomina fase de establecimiento; se reserva un circuito (canal) en cada enlace, y la combinación de circuitos o canales define el camino dedicado. Una vez que el camino se establece, se hace la transferencia de datos. Después de transferir todos los datos, los circuitos se liberan.

No existe direccionamiento durante la transferencia de datos. Los conmutadores encaminan los datos de acuerdo a su banda ocupada (FDM) o rodaja de tiempo (TDM). Existe direccionamiento extremo a extremo que se utiliza durante la fase de establecimiento.

**Ventajas**
- La red y sus componentes son sencillos.
- Ancho de banda garantizado.
- Soporta características de Calidad de Servicio (QoS).
- Los retardos son predecibles y constantes una vez establecido el circuito.

**Desventajas**
- Ineficiencia: el circuito permanece reservado aunque no haya transferencia de datos activa.
- Requiere que los equipos de los usuarios sean homogéneos en cuanto a recursos, para aprovechar eficientemente el circuito dedicado.
- Puede haber congestión en las centrales cuando muchos usuarios intentan comunicarse al mismo tiempo.

### Conmutación de Paquetes

- Los mensajes (datos) se dividen en paquetes con un tamaño fijo o variable, por ejemplo, de n bytes (conocido como payload).
- Cada paquete incluye información adicional en su encabezado (header), que contiene datos necesarios para su tránsito por la red.
- Los conmutadores de red (switches o routers) siguen el proceso de store and forward:
    - Reciben el paquete completo.
    - Lo almacenan temporalmente.
    - Lo reenvían por el enlace adecuado hacia su destino.

### Redes de datagramas

En conmutación de paquetes, no hay asignación de recursos para un paquete. Esto significa que no hay ancho de banda reservado en los enlaces, y no hay tiempo de procesamiento planificado para cada paquete.

Los recursos se asignan bajo demanda. La asignación se realiza de acuerdo a una política primero en llegar, primero en ser servido. Cuando el conmutador recibe un paquete, no importa cuál sea el origen o el destino, el paquete debe esperar si hay otros paquetes procesándose.

Cada paquete se trata de forma independiente de los otros y hace el mayor esfuerzo para procesar la mayor cantidad posible y elige el mejor camino. Los paquetes en este esquema se denominan datagramas.

Los datagramas pertenecen al mismo mensaje, pero pueden viajar por caminos diferentes hasta alcanzar su destino. Esto es debido a que los enlaces pueden estar involucrados en la transferencia de paquetes de otros orígenes y no tienen necesariamente ancho de banda disponible para transmitir todos los paquetes de A a X.

Este enfoque puede hacer que los datagramas de una transmisión lleguen al destino desordenados con diferentes retardos entre ellos. Los paquetes pueden también perderse o descartarse debido a la falta de recursos. En la mayoría de los protocolos, es responsabilidad de un protocolo de nivel superior reordenar los datagramas o solicitar los datagramas perdidos antes de pasarlos a la aplicación.

Las redes de datagramas también se conocen en algunas ocasiones como redes no orientadas a conexión ya que el conmutador no mantiene información sobre el estado de la conexión. No hay fase de establecimiento ni de liberación. 

Cada conmutador tiene una **tabla de encaminamiento** que se basa en la dirección destino. Las tablas de encaminamiento son dinámicas y se actualizan periódicamente. La tabla almacena las direcciones destino y los correspondientes puertos de salida de reenvío.

Cada paquete en una red de datagramas tiene una cabecera que contiene la dirección destino del paquete. Cuando el conmutador recibe el paquete, se mira esta dirección y se consulta la tabla de encaminamiento para encontrar el puerto de salida por el cual se debe reenviar el paquete. Esta dirección se mantiene durante todo el recorrido del paquete.

**Ventajas**
- Si se cae un enlace se detecta y usa otro, tiene tolerancia a fallas.
- Facilita la escalabilidad, al haber mínimo control se realiza un rápido procesamiento sin importar la cantidad de usuarios que se estén  atendiendo.

**Desventajas**
-Como no es un canal dedicado no se puede garantizar tasa de transferencia fija o retardo fijo.

### Redes de Circuitos Virtuales

Es una mezcla entre una red de conmutación de circuitos y una red de datagramas. Tiene algunas características de ambas.
1. Existe fase de establecimiento y liberación además de la fase de transferencia de datos. 
2. Los recursos pueden ser asignados durante la fase de establecimiento.
3. Los datos se dividen en paquetes y cada paquete lleva una dirección en la cabecera. Sin embargo, la dirección de la cabecera sólo tiene jurisdicción local (define cuál debería ser el siguiente conmutador y el canal por el cual el paquete debe ser transportado), no jurisdicción extremo a extremo.
4. Todos los paquetes siguen el mismo camino establecido durante la conexión.
5. Se implementa en el nivel de enlace de datos.

**Ventajas de la conmutación de paquetes**
- Mayor eficiencia: los enlaces pueden ser compartidos por múltiples usuarios/paquetes simultáneamente.
- Los paquetes se encolan y transmiten tan pronto como es posible, optimizando el uso de recursos.
- Permite conversión de velocidad entre nodos mediante el uso de búferes (buffers).
- Aunque un enlace esté congestionado, se pueden seguir aceptando paquetes (aunque con mayor retardo).
- Posibilidad de asignar prioridades a los paquetes según su tipo o urgencia.
- Permite transmisión en paralelo de distintos paquetes por rutas diferentes.
- En caso de error, solo se pierde el paquete afectado, no toda la comunicación.

**Desventajas**
- Requiere información de control adicional en cada paquete (overhead).
- Produce retardos variables e impredecibles, lo cual puede afectar aplicaciones sensibles al tiempo.
- La red es más compleja: se necesitan mecanismos de enrutamiento, control de congestión, reordenamiento de paquetes, etc.

## Protocolo de Internet

El nivel de red es responsable de la entrega host a host y del encaminamiento de los paquetes a través de los encaminadores o conmutadores.

El nivel de red en el origen es responsable de crear un paquete a partir de los datos que vienen de otro protocolo. La cabecera del paquete contiene, entre otra información, las direcciones lógicas del origen y del destino.

El nivel de red es responsable de comprobar su tabla de encaminamiento para encontrar la información de encaminamiento. Si el paquete es demasiado grande, se fragmenta.

El nivel de red en el conmutador o encaminador es responsable de encaminar el paquete. Cuando llega un paquete, el encaminador o conmutador consulta su tabla de encaminamiento y encuentra la interfaz por la que el paquete debe ser enviado. El paquete, después de algunos cambios en la cabecera, se pasa de nuevo al nivel de enlace de datos con la información de encaminamiento.

El nivel de red en el destino es responsable de la verificación de la dirección; se asegura que la dirección de destino del paquete es la misma que la dirección de red del host. Si el paquete es un fragmento, el nivel de red espera hasta que todos los fragmentos han llegado, los reensambla y los entrega al nivel de transporte.

En Internet se ha elegido el tipo de servicio no orientado a la conexión en el nivel de red, ya que Internet está compuesto de tantas redes heterogéneas que casi siempre es imposible crear una conexión desde un origen a un destino sin conocer por adelantado la naturaleza de las redes.

Cada dispositivo conectado a Internet tiene al menos una **dirección IP**, que es necesaria para identificarlo dentro de la red y para que los enrutadores puedan reenviar el tráfico correctamente. Los dispositivos en redes privadas basadas en TCP/IP también requieren direcciones IP, que deben coordinarse para evitar conflictos dentro de esas redes. Cuando los dispositivos se conectan a Internet global, se les asignan direcciones que deben ser únicas para evitar duplicados.

### IPv4

IPv4 es un protocolo de datagramas no orientado a conexión y no fiable, utiliza un servicio de mejor entrega posible, es decir que no ofrece control de errores ni control de flujo (sólo para la detección de errores en la cabecera). Si la fiabilidad es importante, IPv4 debe emparejarse con un protocolo fiable como TCP.

Un **datagrama** es un paquete de longitud variable que consta de dos partes: cabecera y datos. La cabecera tiene de 20 a 60 bytes de longitud y contiene información esencial para el encaminamiento y la entrega. En TCP/IP se muestra la cabecera en secciones de 4 bytes.

**Elementos de un datagrama**

- Versión (VER): define la versión del protocolo IPv4.
- Longitud de la cabecera (HLEN): define la longitud total de la cabecera del datagrama en palabras de 4 bytes.
- Tipo de servicio (TOS): campo de 8 bits, los 3 primeros bits definen la prioridad. Los siguientes 4 bits se denominan tipo de servicio y el último no se utiliza.
- Longitud total: campo de 16 bits que define la longitud total (cabecera más datos) del datagrama en bytes.
- Identificación: identifica un datagrama que procede de un host origen. La combinación de la identificación y de la dirección origen IPv4 deben definir de forma única un datagrama cuando deja el host origen. El número de identificación ayuda al destino a reensamblar el datagrama.
- Indicadores (flags): campo de 3 bits. El primer bit está reservado. El segundo bit se denomina bit de no fragmentación. Si su valor es 1, la máquina no debe fragmentar el datagrama. Si no puede pasar el datagrama a través de la red física disponible, lo descarta y envía un mensaje de error ICMP al host origen. Si su valor es 0, el datagrama se puede fragmentar si es necesario. El tercer bit se denomina bit de más fragmentos. Si su valor es 1, significa que el datagrama no es el último fragmento, hay más fragmentos después de él. Si su valor es 0, significa que éste es el último fragmento o que solo hay un fragmento.
- Desplazamiento del fragmento (offset): muestra la posición relativa de este fragmento respecto al datagrama completo.
- Tiempo de vida (TTL): se utiliza para controlar el número máximo de saltos (encaminadores) visitados por el datagrama.
- Protocolo: define el protocolo de nivel superior que utiliza los servicios del nivel IPv4. Un datagrama IPv4 puede encapsular datos de varios protocolos superiores como TCP, UDP, etc.
- Suma de comprobación (checksum): Valor calculado para detectar errores. Se divide la cabecera en secciones de 16 bits y se suman todas ellas.
- Dirección origen: define la dirección IPv4 de un origen. 
- Dirección de destino: define la dirección IPv4 del destino.

#### Fragmentación

Cada protocolo de nivel de enlace de datos tiene su propio formato de trama. Uno de los campos definidos en el formato es el tamaño máximo del campo de datos. Cuando un datagrama se encapsula en una trama, el tamaño total del datagrama debe ser menor que este tamaño máximo.

En IPv4, un datagrama puede ser fragmentado por el host origen o por cualquier encaminador encontrado en el camino, aunque la tendencia es limitar la fragmentación sólo al origen.

El reensamblado del datagrama sólo se hace en el host destino ya que sólo en el destino se puede asegurar que todos los fragmentos lleguen ahí.

El host o encaminador que fragmenta un datagrama debe cambiar el valor de tres campos: indicadores, desplazamiento del fragmento y longitud total. El resto de los campos deben ser iguales y el valor del checksum debe recalcularse.

La cabecera de un datagrama IPv4 está compuesta de dos partes: una parte fija y una parte variable. La parte fija tiene una longitud de 20 bytes y la parte variable comprende las opciones que pueden ocupar un máximo de 40 bytes. No son requeridas para un datagrama, se pueden utilizar para probar y depurar la red.

Cuando un paquete IPv4 es enviado desde un host a través de una red, pasa por uno o varios routers antes de llegar a su destino. Durante este recorrido, algunos campos del encabezado IP deben ser modificados por cada router.

El primer campo que cambia es el TTL (Time To Live). Este campo se utiliza para limitar la vida útil del paquete en la red y evitar que quede circulando indefinidamente. 

Como el TTL se modifica, también debe cambiar otro campo: el Header Checksum. Este es un valor de verificación que garantiza la integridad del encabezado IP. Al cambiar el TTL, el router debe recalcular el checksum para reflejar el nuevo valor.

#### Direcciones IPv4

Las direcciones IPv4 se clasifican en varios tipos:
- Unicast: Identifican una única interfaz de red.
- Broadcast: Direcciones especiales para enviar mensajes a todos los dispositivos en una red.
- Multicast: Direcciones usadas para enviar mensajes a múltiples interfaces que forman parte de un grupo. 
- Anycast: Direcciones asignadas a un conjunto de interfaces, donde el tráfico se enruta hacia el más cercano.

Originalmente, las direcciones IPv4 unicast se dividían en dos partes: número de red y número de host. Se establecieron cinco clases (A, B, C, D y E) para asignar diferentes cantidades de bits a cada parte, equilibrando la cantidad de redes y hosts disponibles.
- Las clases A, B y C se utilizan para unicast.
- La clase D es para multicast.
- La clase E está reservada para uso experimental.

Sin embargo, este esquema tuvo problemas de escalabilidad: la asignación centralizada de números de red era incómoda y generaba desperdicio de direcciones, especialmente en clases A y B.

#### Subnetting

Para mejorar la asignación de direcciones y permitir la subdivisión local de un bloque de direcciones, se introdujo el direccionamiento por subredes. Esto permite que un sitio reciba un bloque de direcciones y lo divida en subredes más pequeñas.

La máscara de subred es una cadena de bits que determina qué parte de la dirección IP corresponde a la red/subred y cuál a los hosts. Un bit en 1 indica que la posición es parte de la red/subred, mientras que un bit en 0 indica la parte de host. Los dispositivos usan esta máscara para decidir cómo enrutar los paquetes.

**Direcciones Especiales en IPv4**
- Dirección de difusión (broadcast): en cada subred, se reserva una dirección con todos los bits de host en 1 para enviar mensajes a todos los dispositivos en esa subred.
- Broadcast limitado (255.255.255.255): Direcciona todos los dispositivos en la red local y no es reenviado por routers.
- 0.0.0.0/8: Este host en esta red
- 127.0.0.0/8: Loopback, es una dirección IP especial que permite a un host enviarse datos a sí mismo.

#### NAT 

NAT permite a un usuario tener internamente un gran conjunto de direcciones y una dirección, o un conjunto de pequeñas direcciones, de cara al exterior. El tráfico interior puede usar el conjunto grande; el tráfico exterior el conjunto pequeño. 

Para separar las direcciones usadas dentro del hogar o el negocio y las usadas para Internet, las autoridades de Internet han reservado tres conjuntos de direcciones como direcciones privadas: 10.0.0.0/8, 172.16.0.0/12 y 192.168.0.0/16

La administración de este espacio es local y suele combinarse con NAT (traducción de direcciones de red), para que los paquetes puedan salir a Internet con una dirección pública válida.

Todos los paquetes de salida pasan a través del enrutador NAT, que sustituye la dirección origen en el paquete con la dirección global NAT. Todos los paquetes de entrada pasan también a través del enrutador NAT, que sustituye la dirección destino en el paquete con la dirección privada apropiada.

### IPv6

IPv4 presenta limitaciones estructurales que afectan su escalabilidad y funcionalidad en la Internet moderna. El principal problema es el espacio reducido de direcciones, que ha llevado al uso de mecanismos transitorios como NAT, CIDR y subredes. Además, IPv4 no incluye soporte obligatorio para funciones de seguridad como cifrado y autenticación.

Ante esta situación, se definió IPv6 como una nueva versión del protocolo IP. IPv6 ofrece un espacio de direcciones mucho más amplio, permite la autoconfiguración de dispositivos, mejora la eficiencia del procesamiento de paquetes y agrega soporte nativo para seguridad y calidad de servicio.

La cabecera base ocupa 40 bytes, mientras que las cabeceras de extensión y los datos del nivel superior pueden ocupar hasta 65.535 bytes de información.

**Elementos de la cabecera base**
- Versión: define el número de versión.
- Prioridad: define la prioridad del paquete respecto a la congestión de tráfico.
- Etiqueta de flujo: diseñado para ofrecer un tratamiento especial para un flujo de datos particular.
- Longitud de la carga: define la longitud del datagrama IP excluyendo la cabecera base.
- Cabecera siguiente: define la cabecera que sigue a la cabecera base en el datagrama. La cabecera siguiente es una de las cabeceras de extensión opcionales utilizadas por IP o un paquete encapsulado de UDP o TCP.
- Límite de salto: tiene el mismo objetivo que el campo TIL en IPv4.
- Dirección origen: especifica la dirección del origen.
- Dirección destino: contiene la dirección del destino. Si se utiliza encaminamiento desde el origen, este campo contiene la dirección del siguiente encaminador.

A diferencia de IPv4, la cabecera IPv6 no incluye un campo de checksum, ya que se considera responsabilidad de los protocolos de transporte superiores garantizar la integridad de los datos.

Las direcciones IPv6 pueden ser de diferentes tipos:
- Direcciones link-local: válidas solo en el enlace local, se utilizan para autoconfiguración y no son reenviadas por routers.
- Direcciones globales (global unicast): ruteables y accesibles desde Internet, equivalentes a las direcciones públicas en IPv4.
- Direcciones locales únicas (ULA): válidas dentro de una organización o conjunto de enlaces, no deben ser ruteadas hacia el exterior. 
- Direcciones especiales: incluyen ::/128 (no especificada), ::1/128 (loopback), y 2001:db8::/32 (reservada para documentación).

IPv6 utiliza prefijos especiales para indicar el ámbito de una dirección, es decir, el área donde es válida:
- Node-local: Solo para comunicación dentro del mismo dispositivo.
- Link-local: Solo para nodos en el mismo enlace o red física local.
- Global: Válida para toda la Internet.

#### Configuración

Los IIDs (Interface Identifiers) son los 64 bits menos significativos de una dirección IPv6 unicast. Deben ser únicos dentro del mismo prefijo de red y pueden generarse de dos formas:
- A partir de la dirección MAC del dispositivo.
- Generados aleatoriamente para proteger la privacidad y evitar rastreos.

**Stateless (SLAAC) Autoconfiguración de Dirección sin Estado**

La interfaz genera su dirección automáticamente combinando el prefijo de red con su IID. El objetivo de SLAAC es permitir que los dispositivos se autoconfiguren automáticamente una dirección link-local sin ayuda externa.

Proceso general de SLAAC en IPv6:
- Obtener una dirección link-local.
- Verificar si está en uso en la red (detección de duplicados - DAD).
- Formar direcciones globales combinando un prefijo anunciado por el router con un identificador de interfaz.

**Detección de Dirección Duplicada (DAD)**
Antes de usar una dirección IPv6, el host debe verificar que no esté en uso por otro dispositivo. Esto se hace con el mecanismo DAD (Duplicate Address Detection) mediante mensajes ICMPv6:
- El host genera una dirección (por ejemplo, una dirección basada en su MAC).
- Envía mensajes Neighbor Solicitation al grupo multicast correspondiente.
- Si alguien responde con un Neighbor Advertisement, significa que la dirección está en uso, y DAD falla: la dirección no se utiliza.
- Si no hay respuesta, la dirección se considera única y pasa al estado de dirección preferida.

SLAAC para Direcciones Globales en IPv6

Una vez que el nodo tiene su dirección link-local, puede necesitar direcciones globales.
- El router anuncia un prefijo global en sus mensajes Router Advertisement.
- El host toma este prefijo y le agrega su identificador de interfaz (IID).
- La dirección resultante se considera global y sus tiempos de validez y preferencia se derivan de lo indicado por el router.

**Stateful (DHCP Protocolo de Configuración Dinámica de Host)**
Un servidor central administra y asigna las direcciones a los dispositivos. Es un protocolo cliente-servidor utilizado para asignar información de configuración a los hosts.

DHCP se utiliza principalmente para asignar automáticamente:
- Dirección IP
- Máscara de subred
- Dirección IP del router (gateway)
- Dirección IP del servidor DNS

IPv6 utiliza el prefijo FF00::/8 para definir **direcciones multicast**. Estas direcciones permiten enviar un solo paquete a múltiples destinatarios al mismo tiempo. El segundo byte de la dirección incluye flags de uso y un campo que define el alcance (scope), como interface-local, link-local, site-local u organization-local.

La **Autoridad de Números Asignados en Internet (IANA)** administra las direcciones IP.
La **Corporación para la Asignación de Nombres y Números en Internet (ICANN)** mantiene los registros de recursos numéricos de la IANA y es responsable de asignar las direcciones del protocolo de Internet (IPv4 e IPv6) y los números de sistema autónomo.

### ARP

A nivel de red, hosts y routers se identifican con direcciones lógicas (IP), únicas a nivel mundial. A nivel físico, se usan direcciones físicas (MAC), únicas dentro de una red local.

Se necesitan ambos tipos de dirección, porque:
- Una red física (como Ethernet) puede usar múltiples protocolos de red.
- Un protocolo de red puede operar sobre varias redes físicas.

Necesitamos poder mapear direcciones lógicas a físicas y viceversa.

Cuando un host o router quiere enviar un datagrama IP, necesita encapsularlo en una trama de enlace. Para eso, debe conocer la dirección física del destinatario, y se puede utilizar el **protocolo ARP** para obtener la dirección física a partir de la lógica.

**Pasos del funcionamiento de ARP**
1. El emisor conoce la IP de destino.
2. IP le pide a ARP crear un paquete de solicitud que incluye: Dirección física del emisor, Dirección IP del emisor, Dirección IP del destinatario (La dirección MAC del destino se deja en ceros porque aún no se conoce)
3. Se encapsula en una trama y se envía en broadcast a la capa de enlace.
4. Todos los nodos la reciben, pero solo el correcto responde.
5. El nodo destino responde con un mensaje ARP de respuesta (unicast) que contiene su MAC.
6. El emisor recibe la respuesta y guarda la dirección MAC del destino.
7. El datagrama IP original se encapsula en una nueva trama Ethernet y se envía unicast al destino

### ICMP

El protocolo IP tiene dos deficiencias:
- Falta de control de errores.
- Falta de mecanismos de asistencia.

También hay eventos los cuales IP no puede notificar:
- Si un router debe descartar un datagrama porque no puede encontrar una ruta al destino final.
- Si el campo "tiempo de vida" (TTL) llega a cero.
- Si el host de destino debe descartar todos los fragmentos de un datagrama porque no los ha recibido todos dentro del tiempo límite.

Además, el protocolo IP carece de un mecanismo para consultas entre hosts o de administración. A veces un host necesita saber si otro host o router está activo. O un administrador de red puede necesitar información de otro host o router.

Para cubrir estas necesidades, se diseñó el **Protocolo de Mensajes de Control de Internet (ICMP)**.

Los mensajes ICMP se dividen en dos grandes categorías:
- Mensajes de reporte de errores: informan sobre problemas que un router o un host (de destino) pueden encontrar al procesar un paquete IP.
- Mensajes de consulta (query): Aparecen en pares (solicitud y respuesta) y ayudan a un host o a un administrador de red a obtener información específica de un router u otro host.

**Formato de los mensajes ICMP**

Un mensaje ICMP tiene:
- Un encabezado de 8 bytes
- Una sección de datos de tamaño variable

**Elementos del encabezado**
- Tipo (Type): especifica el tipo de mensaje.
- Código (Code): indica la razón específica para ese tipo.
- Checksum: verificación de errores.
- Content: contenido específico.

ICMP maneja cinco tipos de errores:
1. Destino inalcanzable: Cuando un router no puede enrutar un datagrama o un host no puede entregarlo, el datagrama se descarta y se envía un mensaje "Destino inalcanzable" (tipo 3) al host de origen que lo envió. El campo "código" (code) de este tipo de mensaje indica la razón por la cual el datagrama fue descartado.
2. Atenuación en la fuente: Cuando un router o un host descarta un datagrama debido a congestión, envía un mensaje al host origen que tiene dos propósitos:
    - Informar al origen que el datagrama fue descartado.
    - Advertir al origen que hay congestión en el camino y que debe reducir la velocidad de envío.
3. Tiempo excedido: Se genera en dos casos específicos:
    - Tiempo de vida (TTL) agotado en tránsito.
    - Fragmentos no recibidos a tiempo.
4. Problemas de parámetro: se genera cuando hay ambigüedad o errores en el encabezado del datagrama IP. Si un router o el host de destino detecta que hay un valor erróneo o ausente en algún campo del encabezado IP, el datagrama se descarta y se envía un mensaje ICMP al host origen para notificarlo.
5. Redirección: permite a un router informar a un host en su red local que hay una ruta mejor para alcanzar un destino específico.

Además de reportar errores, ICMP también puede utilizarse para diagnosticar problemas en la red. Esto se logra a través de mensajes de consulta (query), que permiten obtener información entre nodos.

Echo Request - Tipo 8 (Solicitud)
Echo Reply - Tipo 0 (Respuesta)

Se utilizan comúnmente en herramientas como ping para verificar si dos sistemas pueden comunicarse entre sí.

Timestamp Request - Tipo 13 (Solicitud)
Timestamp Reply - Tipo 14 (Respuesta)

Permiten a dos máquinas (hosts o routers) determinar el tiempo de ida y vuelta (RTT).

**Ping**

El programa ping permite verificar si un host está activo y responde.
- El host origen envía mensajes ICMP tipo 8 (Echo Request).
- El destino, si está vivo, responde con mensajes ICMP tipo 0 (Echo Reply).

El programa asigna:
- Un identificador para identificar el proceso.
- Un número de secuencia que incrementa con cada solicitud enviada.
- También inserta la hora de envío en el campo de datos del mensaje, de modo que cuando recibe la respuesta puede calcular el tiempo de ida y vuelta (RTT) restando el tiempo de llegada al tiempo de salida.
- Cuando se interrumpe con Ctrl + C, se imprime un resumen estadístico.

**Traceroute**

Se utiliza para rastrear la ruta que sigue un paquete IP desde el origen hasta el destino.
Traceroute utiliza dos tipos de mensajes ICMP:
- Time Exceeded (Tipo 11)
- Destination Unreachable (Tipo 3, código 3)

Y aprovecha el campo TTL del encabezado IP para provocar intencionalmente respuestas ICMP de los routers intermedios.

#### ICMPv6

En IPv6, el protocolo ICMP se utiliza tanto para reportar errores en el procesamiento de paquetes como para realizar funciones auxiliares de la capa de red, tales como autoconfiguración, descubrimiento de vecinos y gestión de grupos multicast.

Un mensaje ICMPv6 está compuesto por los siguientes campos:
- Type (8 bits): indica el tipo de mensaje y determina el formato de los campos siguientes.
- Code (8 bits): depende del tipo de mensaje e indica información adicional sobre el motivo del mensaje.
- Checksum (16 bits): cubre el contenido del mensaje ICMPv6 y parte del encabezado IPv6 para asegurar la integridad.
- Message Body: contiene datos específicos del tipo de mensaje, de longitud variable.

El protocolo de descubrimiento de vecinos reemplaza y amplía funciones que en IPv4 eran cubiertas por otros protocolos. **Neighbor Discovery (ND)** utiliza mensajes ICMPv6 para que los nodos puedan interactuar en un mismo enlace.

Entre sus funciones principales se incluyen:
- Descubrir routers en el mismo enlace.
- Obtener prefijos y parámetros de red (MTU, hop limit, etc.).
- Autoconfiguración de direcciones mediante SLAAC.
- Resolución de direcciones de capa de enlace (MAC).
- Detección de direcciones duplicadas (Duplicate Address Detection).
- entre otros.

**Objetivos de ND e IND**
- ND: Permite a los hosts encontrar routers cercanos que puedan reenviar sus paquetes.
- ND: Permite descubrir las direcciones de enlace (MAC) de los vecinos.
- IND: Permite descubrir la dirección IPv6 de un nodo vecino, conociendo solo su dirección MAC.

**Router Solicitation (Tipo 133)**
- El host envía este mensaje para descubrir un router en la red local.
- Equivalente al mensaje usado en IPv4 para buscar puerta de enlace predeterminada.
- Puede incluir la dirección física del host para facilitar la respuesta.

**Router Advertisement (Tipo 134)**
- Es enviado periódicamente por routers o como respuesta a un RS, informando prefijos válidos, MTU y otros parámetros.

**Neighbor Solicitation (Tipo 135)**
- Es equivalente a un ARP Request en IPv4.
- Se envía cuando un nodo conoce la dirección IPv6 de su vecino, pero necesita su dirección MAC.

**Neighbor Advertisement (Tipo 136)**
- Respuesta al mensaje anterior. Equivale al ARP Reply.
- Incluye varias banderas:
    - R (Router): Si está en 1, indica que el emisor es un router.
    - S (Solicited): Si está en 1, la respuesta es a una solicitud específica.
    - O (Override): Si está en 1, la información reemplaza la que ya existe en la caché del receptor.

**Inverse Neighbor Solicitation (Tipo 141)**

Se usa cuando un nodo conoce la dirección MAC de su vecino, pero no su dirección IPv6.
Se envía a una dirección multicast.
Incluye:
- Dirección MAC del emisor
- Dirección MAC del nodo buscado
- Opcionalmente, la dirección IPv6 del emisor y el MTU del enlace

**Inverse Neighbor Advertisement (Tipo 142)**

Es la respuesta al mensaje anterior.
El emisor incluye su propia dirección MAC y la del nodo destino.
Permite que el solicitante descubra la dirección IPv6 correspondiente.

# Ruteo

El ruteo es una función fundamental de la capa de red cuyo objetivo es determinar el camino que deben seguir los paquetes IP desde un host origen hasta un host destino, atravesando una red de routers interconectados. 

Esta tarea implica elegir el mejor camino posible usando la tabla de ruteo que consulta cada vez que necesita enviar un datagrama. Cuando un paquete llega, consulta su tabla de ruteo para determinar por cuál de sus interfaces debe reenviar el paquete.

**Entrega Directa**

En una entrega directa, el destino final del paquete es una estación conectada a la misma red física en la que se encuentra el entregador.

La entrega directa ocurre cuando el emisor y el destino del paquete se encuentran localizados en la misma red física o cuando la entrega se realiza entre el último encaminador y la estación destino. Esto ocurre, por ejemplo, en redes locales (LAN) donde los dispositivos están conectados a través de un switch o hub.

El emisor puede fácilmente determinar si la entrega es directa. Puede extraer la dirección de red del destino (utilizando una máscara) y comparar esta dirección con las direcciones de las redes a las que se conecta. Si coincide, la entrega es directa.

**Entrega Indirecta**

Si la estación destino no está en la misma red que el entregador, el paquete se entrega de forma indirecta. En una entrega indirecta, el paquete va de encaminador a encaminador hasta que alcanza a uno conectado a la misma red física que su destino final. Una entrega siempre involucra una entrega directa (la última) y cero o más entregas indirectas.

En una entrega indirecta, el destino final no se encuentra en la misma red que el emisor, por lo que se requiere la intervención de uno o más routers para alcanzar el destino.

Aspectos adicionales:
- Si el paquete sale desde una red privada con direcciones no enrutable en Internet (como 10.x.x.x), el primer router debe aplicar NAT para asignar una dirección IP pública al paquete.
- El datagrama IP conserva las mismas direcciones IP de origen y destino, salvo que se aplique NAT.
- La dirección MAC (u otra dirección de capa de enlace) cambia en cada salto.

El objetivo del ruteo es encontrar el camino de menor costo entre dos nodos del grafo. En el caso en que todos los enlaces tienen el mismo costo, el camino de menor costo coincide con el camino más corto, es decir, aquel con menor cantidad de saltos intermedios.

**Tipos de algoritmos de ruteo**

Los algoritmos de ruteo pueden clasificarse de diferentes maneras, dependiendo de sus características.

***Según el conocimiento de la red***
- Algoritmos globales: utilizan información completa de la red para calcular las rutas. Esto implica conocer la topología completa y los costos de todos los enlaces.
- Algoritmos descentralizados: no disponen de una vista global de la red. Cada nodo sólo conoce el costo de los enlaces directamente conectados y estima las distancias a los demás nodos.

***Según su dinámica***
- Algoritmos estáticos: las rutas se configuran manualmente o cambian muy lentamente, generalmente como resultado de intervención humana.
- Algoritmos dinámicos: adaptan las rutas automáticamente en función de los cambios en la topología o el tráfico de la red. Pueden ejecutarse periódicamente o en respuesta directa a eventos como la caída de un enlace o la variación del costo de un enlace. 

# TCP

El nivel de transporte es el responsable de la entrega de un mensaje entero de proceso a proceso (comunicación fiable de extremo a extremo). Asegura que el mensaje completo llega intacto y en orden, supervisando el control de errores y el control de flujo en el nivel de origen a destino.

La cabecera del nivel de transporte debe incluir un tipo de dirección denominada número de puerto para saber a qué proceso se realiza la entrega.

**Diferencias y similitudes con la capa de enlace**

Ambos son fiables, implementan control de errores y flujo mediante ventanas. 
Las diferencias están en que en la capa de enlace se cuentan tramas y la ventana es fija. En la capa de transporte se cuentan bytes y la ventana es dinámica.

Aunque hay varias formas de conseguir la comunicación entre procesos, la más frecuente es usar el paradigma cliente/servidor. Un proceso de la computadora local, denominado un cliente, necesita servicio desde un proceso que habitualmente está situado en un proceso remoto, denominado un servidor.

Los **números de puertos** son utilizados para multiplexar servicios en los hosts. Esto permite que un mismo host provea distintos servicios a través de una única dirección IP. La consecuencia de no contar con ese campo en el header de la PDU es la incapacidad de identificar a qué servicio va destinado ese segmento.

El número de puerto de destino es necesario para la entrega y el número de puerto en origen es necesario para la respuesta. El cliente define su propio puerto, elegido aleatoriamente por el software de nivel de transporte que se ejecuta en el cliente.

El servidor también debe definir su propio puerto. Sin embargo, este tipo de puerto no se puede elegir aleatoriamente. Se utilizan números de puerto universales, los denominados **números de puerto bien conocidos**.

La **IANA (Internet Assigned Number Authority)** ha dividido los números de puerto en tres rangos: bien conocidos, registrados y dinámicos (o privados)
- Puertos bien conocidos. Los puertos entre 0 y 1023 son asignados y controlados por IANA.
- Puertos registrados. Los puertos entre 1024 y 49.151 no son asignados o controlados por IANA. Sólo pueden ser registrados en IANA para evitar la duplicación.
- Puertos dinámicos. Los puertos entre 49.152 y 65.535 no son controlados ni registrados. Pueden ser usados por cualquier proceso.

La comunicación proceso a proceso necesita dos identificadores, dirección IP y número de puerto, en cada extremo para poder crear una conexión. La combinación de una dirección IP y un número de puerto se denomina **dirección de socket**. La dirección del socket cliente define al proceso cliente de forma única, al igual que la del socket del servidor define al proceso servidor.

## ARQ

Una manera sencilla de enfrentar la pérdida de paquetes (y errores de bits) es retransmitir el paquete hasta que se reciba correctamente. Esto requiere un mecanismo para determinar:
- Si el receptor recibió el paquete.
- Si el paquete recibido es efectivamente el que el emisor envió.

El método para que el receptor notifique al emisor que ha recibido el paquete se llama reconocimiento (ACK). En su forma más básica:
- El emisor envía un paquete y espera un ACK.
- Cuando el receptor lo recibe, envía el ACK.
- Cuando el emisor recibe el ACK, envía otro paquete, y el proceso continúa.

Si un ACK se pierde, el emisor no puede distinguir si se perdió el ACK o el paquete original, así que simplemente vuelve a enviar el paquete. Esto significa que el receptor puede recibir copias del mismo paquete, por lo que debe estar preparado para manejar duplicados.

Se usan códigos de detección de errores (como checksums) que permiten detectar errores de manera eficiente. Cuando un receptor detecta un error en un paquete, no envía un ACK, y eventualmente el emisor lo retransmitirá.

Aún con este escenario básico, es posible que el receptor reciba copias duplicadas del mismo paquete. Para manejar esto, se utiliza un número de secuencia. Cada paquete único recibe un número de secuencia cuando se envía, y el receptor puede usar ese número para identificar duplicados y descartarlos.

Este protocolo es fiable pero no muy eficiente. Si hay mucha latencia, el emisor solo puede enviar un paquete a la vez y debe esperar un ACK para continuar. Este protocolo se conoce como stop and wait.

El rendimiento de este esquema está limitado por el tamaño del paquete (M) y el tiempo de ida y vuelta (RTT), y se calcula como M/R. Si el RTT es grande, el rendimiento disminuye. Si hay pérdidas, el rendimiento efectivo puede ser aún peor.

Una solución es permitir que haya más de un paquete en tránsito a la vez. Esto requiere que el emisor decida cuántos paquetes puede enviar sin recibir un ACK. También necesita mantener una copia de cada paquete no reconocido, y temporizadores individuales para gestionar retransmisiones.

El receptor, por su parte, debe tener un mecanismo para distinguir qué paquetes fueron recibidos, cuáles faltan y cuáles están fuera de orden, y almacenarlos temporalmente.

Este esquema se llama **protocolo de ventana deslizante**.
- La “ventana” representa el conjunto de paquetes enviados pero aún no reconocidos.
- A medida que se reciben ACKs, la ventana se desliza y se pueden enviar nuevos paquetes.

El receptor también tiene su propia ventana que lleva seguimiento de los datos recibidos y los que espera. Sin embargo, este modelo no resuelve completamente los problemas de qué tan grande debe ser la ventana ni qué ocurre si el receptor o la red no pueden procesar el ritmo de envío del emisor.

Si el receptor es más lento que el emisor, se necesita un mecanismo para forzar al emisor a reducir su velocidad. A esto se lo llama control de flujo.

Hay dos métodos comunes:
- Control de flujo basado en tasa: Se asigna una velocidad fija de envío al emisor.
- Control de flujo basado en ventana: El tamaño de la ventana puede variar con el tiempo.

El receptor envía una señal al emisor con el tamaño de ventana permitido, lo que se llama anuncio de ventana. Esto puede ir incluido junto al ACK. Así, el emisor ajusta su ventana de transmisión.

Esto permite que el emisor envíe hasta W paquetes sin esperar un ACK, donde W es el tamaño de la ventana.
La tasa de transferencia se aproxima a (S×W)/R, donde S es el tamaño del paquete y R es el RTT.

Una de las decisiones más críticas en un protocolo fiable es cuánto tiempo debe esperar el emisor antes de retransmitir un paquete. Esto se llama **tiempo de espera de retransmisión (RTO)**.

Idealmente, este tiempo debe incluir:
- El tiempo de envío,
- El tiempo de procesamiento en el receptor,
- El tiempo para enviar el ACK,
- El tiempo de procesamiento del ACK en el emisor.

Pero estos valores no se conocen con certeza y pueden variar. Por eso, el protocolo debe estimar el RTT (Round-Trip Time), usando técnicas estadísticas. El estimador se basa en el promedio de muestras de RTT.

TCP es orientado a conexión, confiable y ofrece un flujo de bytes. **Orientado a conexión** significa que las aplicaciones deben establecer una conexión TCP antes de intercambiar datos. Solo hay dos extremos en una conexión TCP; no existe broadcasting ni multicasting con TCP.

Cuando TCP envía un grupo de segmentos:
- Establece un único temporizador de retransmisión (no uno por segmento).
- Si no se recibe ACK a tiempo, retransmite.
- TCP ajusta el tiempo de espera conforme recibe ACKs.

Cuando TCP recibe datos, envía un ACK:
- El ACK puede demorarse una fracción de segundo.
- Los ACKs son acumulativos: si el receptor recibe hasta el byte N, envía ACK = N + 1. Esto proporciona tolerancia ante pérdida de ACKs, ya que el siguiente ACK probablemente cubrirá el segmento anterior.

TCP ofrece un servicio **full-duplex**, es decir, datos pueden fluir simultáneamente en ambas direcciones. Cada extremo mantiene su propio número de secuencia.

Cuando un segmento TCP llega:
- La ventana puede deslizarse.
- El tamaño de la ventana puede cambiar.

TCP descarta duplicados y reordena paquetes fuera de orden si es necesario, ya que IP no garantiza ni orden ni unicidad.

TCP nunca entrega datos fuera de orden a la aplicación; si faltan datos, espera hasta recibirlos todos antes de entregarlos.

## Header TCP

TCP se encapsula dentro de datagramas IP. El encabezado TCP aparece inmediatamente después del encabezado IP (o del último encabezado de extensión en IPv6) y suele tener 20 bytes de longitud cuando no hay opciones TCP. Con opciones, el encabezado TCP puede tener hasta 60 bytes.

Las opciones comunes incluyen:
- Tamaño Máximo de Segmento (MSS)
- Timestamps
- Escalamiento de ventana (Window Scaling)
- ACKs selectivos (SACK)

**Elementos del header TCP**

- Puerto de origen y puerto de destino: junto con las direcciones IP origen y destino del encabezado IP, identifican de manera única una conexión TCP.
- Campo Número de Secuencia (Sequence Number): identifica el primer byte de datos del segmento dentro del flujo de datos. Cada byte tiene un número de secuencia único.
- Campo de Acknowledgment: contiene el número de secuencia que el emisor del ACK espera recibir a continuación. Esto significa que el ACK está reconociendo todos los datos hasta el byte anterior al indicado en ese campo. Este campo sólo es válido si el bit ACK está activado, lo cual ocurre en todos los segmentos excepto los de inicio y cierre de conexión.
- Longitud del Encabezado (data offset): Indica la longitud del encabezado en palabras de 32 bits. Con 4 bits de longitud, el máximo valor posible del encabezado TCP es 60 bytes (con opciones). Si no hay opciones, el tamaño es 20 bytes.
- Bits de Control TCP (flags): son bits de control que indican el propósito o estado de cada segmento TCP. Uno o más pueden estar activos al mismo tiempo.
    - URG — Urgente (el campo Urgent Pointer es válido; raramente usado). (Transmisión de datos)
    - ACK — Acknowledgment (el campo ACK es válido; siempre está activo después de establecer la conexión). (Se usa en las 3 etapas de una conexion)
    - PSH — Push (el receptor debe entregar los datos inmediatamente a la aplicación; no muy utilizado). (Transmisión de datos)
    - RST — Reset (aborta la conexión, generalmente por error). (Transmisión de datos)
    - SYN — Synchronize (inicia la conexión TCP). (Establecimiento de la conexión)
    - FIN — Finaliza la transmisión de datos del emisor. (Cierre de la conexión)
- Tamaño de Ventana (Window Size): indica cuántos bytes, a partir del ACK, el receptor está dispuesto a aceptar. El tamaño de ventana máximo es 65.535 bytes. Para redes rápidas o de alta latencia, esto limita el rendimiento. TCP usa la opción Window Scale para ampliar ese valor y mejorar el rendimiento.
- Checksum TCP: TCP incluye un checksum obligatorio que cubre el encabezado TCP, los datos de la aplicación y algunos campos del encabezado IP. 
- Urgent Pointer: Este campo sólo es válido si el bit URG está activado. Es un desplazamiento positivo que se suma al número de secuencia del segmento. Indica el número de secuencia del último byte de datos urgentes.
- Opciones TCP: 
    - MSS (Maximum Segment Size): Especifica el tamaño máximo de segmento que el emisor está dispuesto a recibir. Se incluye normalmente en los primeros segmentos (con SYN) de una conexión.
    - Otras opciones incluyen: SACK (Selective Acknowledgment), Timestamp, Window Scale.

Cuando se inicia una conexión:
- El bit SYN está activado.
- El campo Sequence Number contiene el número de secuencia inicial (ISN) elegido para esa dirección de la conexión. El número no es 0 ni 1, sino uno aleatorio por seguridad.
- El primer byte de datos enviado tendrá número de secuencia = ISN + 1 (el SYN consume un número de secuencia).
- Los segmentos SYN, FIN y los datos de la aplicación usan números de secuencia y por lo tanto son entregados de forma confiable.
- Los ACKs no consumen número de secuencia y no son retransmitidos por TCP.

**TCP como protocolo de ventana deslizante con ACKs acumulativos**

El campo ACK indica el mayor byte recibido en orden más 1.
Por ejemplo, si el receptor recibe correctamente los bytes 1 a 1024, y luego recibe un segmento con bytes fuera de orden, no puede reconocer aún este último con el campo ACK regular. Para esto se usa la opción SACK (Selective Acknowledgment), que permite al receptor notificar qué datos fuera de orden ha recibido correctamente.

TCP también usa ACKs duplicados (varios ACKs con el mismo número) como señal de pérdida o reordenamiento, útiles para control de errores y congestión.

## Establecimiento y terminación de conexión

**Establecimiento de conexión (three-way handshake)**
- El host A envía un segmento SYN al host B, este segmento contiene el número de secuencia inicial (ISN) del host A, el bit SYN está activado.
- El host B responde con un segmento SYN+ACK, este segmento tiene el bit SYN activado, contiene su propio ISN, y el campo ACK reconoce el ISN de A más uno.
- Finalmente, el host A responde con un segmento ACK, reconociendo el ISN de B más uno. Después de este intercambio de tres segmentos, la conexión está establecida, y ambos extremos han acordado los números de secuencia iniciales

Cada ISN es elegido de forma independiente y aleatoria. Esto:
- Aumenta la seguridad.
- Ayuda a evitar conflictos de conexiones antiguas aún en tránsito.

**Passive Open (Apertura pasiva)**
- Es el estado en el que un servidor TCP espera conexiones entrantes.
- El servidor no inicia la conexión, simplemente espera que otro host (el cliente) se conecte.
- El servidor llama a funciones como listen() y accept() (en programación de sockets).

**Active Open (Apertura activa)**
- Es el proceso en el que un cliente TCP inicia activamente una conexión con otro host.
- El cliente llama a funciones como connect().
- Envía un segmento SYN para comenzar el three-way handshake.

Durante el SYN y el SYN+ACK, es cuando se puede intercambiar una serie de opciones TCP. Algunas de las más comunes incluyen:
- Tamaño Máximo de Segmento (MSS): Cada lado anuncia el tamaño máximo de segmento TCP que está dispuesto a aceptar.
- Opciones para Control de Congestión: Como ECN (Explicit Congestion Notification) o ventanas ampliadas (Window Scaling).
- Timestamps (Sellos de tiempo): Utilizados para mejorar la estimación del RTT y para proteger contra secuencias antiguas.

**Terminación de conexión (four-way handshake)**
La terminación de una conexión TCP se realiza mediante el intercambio de cuatro segmentos, cada lado debe cerrar su mitad de la conexión de forma independiente. Esto significa que una conexión puede estar cerrada en una dirección pero aún abierta en la otra.
- El host A envía un segmento FIN, esto indica que A no tiene más datos para enviar.
- El host B responde con un ACK, confirmando que recibió el FIN.
- Más tarde, cuando el host B también quiere cerrar su lado, envía su propio FIN.
- El host A finalmente responde con un ACK.

Ambos lados están cerrados y la conexión finaliza.

El “Half Close” se refiere a este comportamiento en el cual un host puede cerrar su canal de envío (enviar FIN), pero seguir recibiendo datos del otro extremo. Esto es útil cuando, por ejemplo, el cliente ha terminado de enviar datos, pero espera una respuesta del servidor.

## Retransmisión

Cuando el receptor necesita tiempo para procesar los datos recibidos, puede temporalmente cerrar la ventana (es decir, ponerla en 0). Esto frena el emisor, ya que TCP nunca debe enviar más allá de lo que permite la ventana del receptor.

El problema aparece si:
- El receptor no envía ningún segmento posterior (ni siquiera con ACK o actualización de ventana).
- El emisor queda bloqueado, sin saber si debe seguir esperando o si la red falló.

Para evitar el estancamiento, TCP implementa un temporizador persistente (persist timer).
- Cuando el emisor recibe un segmento con ventana = 0: Inicia el temporizador persistente.
- Al expirar, envía un sondeo de ventana (1 byte de datos o un ACK). Si el receptor responde y actualiza la ventana, el emisor puede reanudar la transmisión.
- Si el receptor sigue informando una ventana de 0, el emisor continúa reactivando el temporizador para seguir sondeando periódicamente.

Este mecanismo garantiza que el emisor no quede bloqueado para siempre, incluso si el
segmento de actualización de ventana se pierde en la red.

Una **retransmisión rápida (fast retransmit)** es un mecanismo mediante el cual TCP puede detectar la pérdida de un segmento sin necesidad de esperar a que expire el temporizador de retransmisión (RTO). Esto mejora enormemente la eficiencia y el rendimiento.

Cuando un receptor TCP recibe segmentos fuera de orden, debe:
- Ignorar el segmento fuera de orden (no puede entregarlo a la aplicación aún).
- Enviar un ACK duplicado con el número de secuencia del último byte recibido en orden.

Cuando TCP recibe 3 ACKs duplicados (4 ACKs con el mismo número en total), activa fast retransmit: Retransmite inmediatamente el segmento faltante, sin esperar el RTO.

Después de realizar una retransmisión rápida, no se debe reducir inmediatamente la tasa de transmisión como si hubiera ocurrido una pérdida severa. 
- El emisor duplica el valor de la ventana de congestión (cwnd) tras los 3 ACK duplicados.
- Retransmite el segmento perdido.
- Mientras sigan llegando ACKs duplicados, incrementa ligeramente cwnd (por cada ACK duplicado).
- Cuando llega un ACK nuevo (mayor al número del segmento perdido), restablece la ventana a un valor conservador (usualmente la mitad de la anterior), y reanuda el crecimiento normal.

Este mecanismo:
- Evita colapsar la red reduciendo demasiado la tasa de envío.
- Mantiene el flujo de datos de manera más suave y reactiva.

Con **SACK (Selective ACK)**, el receptor puede informar qué bloques de datos ha recibido fuera de orden. Esta información se incluye en el encabezado TCP, como una opción. Cada bloque SACK contiene un rango de bytes recibidos correctamente. 

Esto permite al emisor:
- Saber exactamente qué segmentos están perdidos.
- Evitar retransmitir segmentos que el receptor ya tiene.

Cuando TCP recibe un segmento fuera de orden, lo guarda y envía un ACK duplicado para el último byte recibido en orden. Esto no indica una pérdida real, pero puede desencadenar una retransmisión rápida si el emisor recibe 3 ACKs duplicados.

En consecuencia, una reordenación puede parecer una pérdida falsa para TCP, provocando retransmisiones innecesarias.

## Tráfico

Durante el establecimiento de una conexión TCP, se intercambia al menos una opción de Maximum Segment Size (MSS). Este valor representa el tamaño máximo de segmento que se va a enviar sin fragmentar, de forma tal que al sumarle la cabecera IP se obtenga un tamaño igual al de la MTU (Maximum Transmission Unit) del enlace. El MSS se anuncia, no se negocia, y suele estar presente en el segmento SYN dentro de las opciones TCP.

**Tipos de tráfico**

- Tráfico interactivo: se caracteriza por mensajes cortos, del tipo pregunta-respuesta. Las unidades de datos son generalmente menores al MSS, y no llenan completamente el segmento. Ejemplos típicos incluyen chats o terminales remotas. 

En redes LAN esto no genera inconvenientes debido a la alta tasa de transferencia y el bajo retardo, pero en redes WAN este comportamiento es ineficiente: un mensaje de 20 bytes puede generar un tráfico de 80 bytes (20 del segmento TCP + 20 del ACK, por duplicado).

Este tráfico tan fragmentado y redundante se conoce como tinygrams. Para reducirlo, se aplican mecanismos como:
- ACK demorado: El receptor espera para ver si debe enviar datos y así "combinar" el ACK con el envío (piggybacking).
- Algoritmo de Nagle: No se pueden enviar más tinygrams hasta recibir el ACK del anterior. Se comporta como un stop-and-wait pero para pequeños segmentos.

- Tráfico masivo o bulk: corresponde a la transferencia de grandes volúmenes de datos, por ejemplo, al descargar archivos. En este tipo de tráfico, los segmentos suelen ser del tamaño máximo permitido por el MSS. TCP realiza control de flujo mediante ventanas deslizantes. Lo importante es la cantidad de bytes transmitidos, limitada por el tamaño de la ventana de recepción anunciada (advertise window).

## Congestión

Cuando un router recibe más datos de los que puede reenviar, se produce **congestión**. En redes conmutadas por paquetes, la única forma de reducir la congestión es bajando la tasa de envío desde el punto de vista del emisor. Desde el punto de vista del router se pueden descartar paquetes o rutear por otras rutas. TCP implementa mecanismos de control de congestión en la capa 4 (transporte) en ambos extremos de la comunicación.

TCP intenta estimar cuántos datos puede enviar sin saturar la red, midiendo el impacto del envío. Su objetivo es maximizar el rendimiento (throughput) sin saturar ni la red ni el receptor. Se adapta dinámicamente a la situación de la red, mediante un mecanismo llamado self-clocking: la tasa de envío se ajusta en función de la tasa de llegada de los ACKs. Si los ACKs llegan rápido, se envía más. Si se demoran, se reduce la tasa de envío.

Los algoritmos de control de congestión de TCP tienen como objetivo responder a tres eventos fundamentales:
- Comienzo de una conexión: El emisor no tiene información sobre la capacidad de la red.
- Pérdida de paquetes: Indica que la red probablemente está congestionada.
- Confirmación exitosa sin pérdida: Sugerencia de que la red puede aceptar más tráfico.

TCP ajusta dinámicamente la ventana de congestión (cwnd) en respuesta a estos eventos, y se combina con la ventana de recepción (rwnd) para determinar cuántos datos puede enviar el emisor.

La política efectiva de envío de TCP puede expresarse como: 

```Ventana efectiva = min(rwnd, cwnd)```

El intercambio comienza conservadoramente: luego del three-way handshake, el emisor no tiene información suficiente como para enviar todos los datos que el receptor puede recibir.

En vez de llenar de golpe la advertise window, TCP utiliza una estrategia gradual:
- Se introduce una variable cwnd (congestion window), que se multiplica por el MSS para conocer los bytes permitidos.
- Se define también un umbral: ssthresh (slow start threshold). Desde el inicio hasta llegar al ssthresh, TCP incrementa cwnd exponencialmente por cada ACK recibido: esto se llama slow start.
- A partir del umbral, el crecimiento es lineal: esta etapa se denomina congestion avoidance.

En cualquier momento, la cantidad de datos que puede enviarse está limitada por el mínimo entre cwnd y awnd (advertise window).

Si ocurre pérdida de segmento por timeout, TCP reacciona bajando cwnd a 1, reduce ssthresh a la mitad, y comienza nuevamente en slow start.

Sin embargo, existe un caso intermedio: Cuando el receptor detecta que llegó un segmento fuera de orden. En lugar de reducir drásticamente la ventana de congestión, TCP aplica una estrategia menos agresiva llamada fast recovery. En esta etapa, se reduce el umbral de slow start (ssthresh) a la mitad, y luego se continúa con un crecimiento más conservador (congestion avoidance), manteniendo un mayor throughput que si se hubiera reiniciado completamente la conexión.

Este enfoque evita decisiones demasiado drásticas cuando la red sólo está experimentando reordenamientos temporales.

## Características principales

Una de las principales características de TCP es su adaptabilidad tanto a LAN como a WAN. Esta adaptabilidad es posible gracias a los mecanismos de:
- Control de congestión, donde se monitorean señales como la pérdida de paquetes o la latencia para regular la tasa de envío.
- Control de flujo, que asegura que el receptor no se sature.
- Timers adaptativos, como el retransmission timer, que se ajustan en función del RTT medido.
- Mecanismos de recuperación de errores, como retransmisiones por timeout o mediante técnicas como Fast Retransmit y Fast Recovery.

Los mecanismos de control de errores, control de flujo y control de congestión en TCP se aplican por conexión. Esto significa que cada conexión TCP entre un cliente y un servidor mantiene su propio conjunto de parámetros y controles, independientemente de otras conexiones que puedan estar activas simultáneamente.

TCP garantiza la confiabilidad en la transmisión de datos. Al recibir segmentos, TCP realiza una serie de acciones para asegurar que los datos sean correctos y estén en el orden adecuado. Detecta errores utilizando mecanismos como el checksum, que permite verificar la integridad del segmento recibido.

Además, TCP es capaz de reordenar los segmentos que llegan fuera de secuencia. También remueve los segmentos duplicados para evitar la entrega redundante de información.
Para controlar el flujo de datos, utiliza números de secuencia (sequence
numbers) que identifican de manera única cada byte transmitido. 

TCP envía acuses de recibo (ACKs) únicamente para los segmentos válidos y que llegan en la secuencia esperada. Si un segmento no es confirmado dentro de un tiempo determinado, el protocolo activa un timer de retransmisión, que provoca el reenvío de ese segmento.

Este temporizador no puede tener un valor fijo, ya que la red puede variar significativamente en condiciones y tiempos de respuesta. Por esta razón, TCP calcula dinámicamente el valor del timer.

