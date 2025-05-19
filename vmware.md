# ¿Qué diferencia hay entre un snapshot y un backup?

    Un snapshot guarda el estado actual de una VM (disco, memoria y configuración) en ese momento para poder volver atrás rápidamente.

    Un backup es una copia completa o incremental de los datos o discos de una VM que se almacena en otro medio o ubicación, y que permite recuperarla en caso de pérdida o desastre.

 Clave: el snapshot depende del almacenamiento de la VM y no es permanente ni seguro a largo plazo; el backup sí.

# ¿Qué pasos seguirías para crear una nueva VM en ESXi?

    Ingresar a vSphere Client (o al host ESXi).

    Ir a Create / Register VM.

    Elegir Create a new virtual machine.

    Ponerle un nombre a la VM.

    Seleccionar el datastore donde se va a guardar.

    Definir:

        Cantidad de CPU.

        Memoria RAM.

        Tamaño y tipo de disco virtual.

        Adaptador de red.

    Montar una imagen ISO para instalar el SO.

    Finalizar y encender la VM.
# ¿Qué es vCenter y qué ventajas aporta frente a administrar directamente en ESXi?

    vCenter Server es la herramienta de administración centralizada de VMware.

    Ventajas:

        Permite administrar varios hosts ESXi desde un solo punto.

        Soporta vMotion, snapshots, alta disponibilidad (HA), y balanceo de carga (DRS).

        Gestión de permisos centralizada.

        Administración de alarmas, inventario, y automatización.

Sin vCenter solo podés administrar cada ESXi de forma aislada.

# Si una VM deja de responder, ¿cómo la apagarías de forma forzada desde vCenter?

    Desde el vSphere Client o vCenter.

    Buscar la VM en la lista.

    Botón derecho → Power → Power Off (forzado, tipo "corte de energía").

    Si eso no funciona, desde el host ESXi usar SSH o la consola directa:

    esxcli vm process list
    esxcli vm process kill --type=force --world-id <ID de la VM>

# ¿Qué requisitos se necesitan para migrar una VM en caliente (vMotion)?

    Que ambos hosts ESXi estén gestionados por el mismo vCenter.

    Que tengan acceso al mismo almacenamiento compartido (NFS, iSCSI, SAN, etc.).

    Que las redes de las VMs estén configuradas igual en ambos hosts.

    Tener la licencia adecuada que soporte vMotion.

    La VM debe tener VMware Tools instaladas y estar encendida.
# ¿Para qué se instalan las VMware Tools en una máquina virtual?

Para mejorar:

    El rendimiento de video y red.

    Sincronización horaria con el host.

    Posibilidad de apagar, reiniciar y suspender la VM desde vCenter.

    Habilitar copy-paste y drag & drop entre la VM y el host.

    Informes de salud y estado de la VM.

# ¿Qué ventajas tiene un hypervisor Type 1 sobre un Type 2?
|Type 1 (bare-metal) |	Type 2 (hosted)
|:-------------------|:---------------|
|Se instala directo en el hardware.|	Se instala sobre un SO existente.
|Mejor rendimiento y estabilidad.|	Más lento, depende del SO host.
|Ideal para producción y datacenters.|	Uso personal o laboratorios.
|Ejemplo: VMware ESXi.|	Ejemplo: VMware Workstation.

# ¿Cuándo conviene hacer un snapshot y cuándo no?

Conviene:

    Antes de hacer actualizaciones de sistema.

    Antes de cambios de configuración críticos.

    Para pruebas temporales.

No conviene:

    Usarlo como reemplazo de backup.

    Mantenerlo activo mucho tiempo (consume espacio y degrada rendimiento).

    En entornos productivos por periodos prolongados.

# ¿Cómo agregarías más memoria RAM a una VM que ya está creada?

    Apagar la VM (salvo que tenga Hot Add habilitado).

    Editar sus propiedades en vCenter.

    Modificar la cantidad de RAM asignada.

    Encender la VM nuevamente.

Si Hot Add está habilitado, se puede hacer en caliente.

# ¿Qué harías si una VM consume más recursos de los asignados y afecta a las demás?

    Verificar el consumo de CPU/RAM desde vCenter.

    Ajustar límites y reservas de recursos.

    Si es necesario:

        Asignarle más recursos.

        Moverla a otro host con vMotion.

        Limitar su prioridad mediante Resource Pools o configuración de shares.

    Investigar por qué consume tanto (posible mal funcionamiento dentro de la VM).

# Diferencia entre Thick Provisioned y Thin Provisioned

Thick Provisioned:

    Al crear el disco virtual, se reserva todo el espacio en disco físico desde el inicio.

    Ej: si asignás 100 GB, ocupa 100 GB reales en el datastore aunque la VM use solo 10 GB.

Thin Provisioned:

    El disco virtual crece según se va usando.

    Ej: si asignás 100 GB, pero la VM usa 10 GB, ocupa solo 10 GB físicos.

    Permite ahorrar espacio, pero hay riesgo de que el datastore se quede sin espacio si varias VMs usan thin.

# ¿Qué es vMotion y cómo funciona?

    vMotion permite migrar una VM encendida de un host ESXi a otro sin downtime.

    Funciona migrando:

        La memoria de la VM en caliente.

        El estado de la CPU.

        Las conexiones de red.

    Requisitos:

        Los hosts deben estar en el mismo vCenter.

        Deben compartir el mismo almacenamiento.

        Tener las redes configuradas de forma idéntica.

# ¿Qué es High Availability (HA) y cómo funciona?

    Es una función de vCenter que permite recuperar automáticamente las VMs si un host ESXi falla.

    Funcionamiento:

        Se agrupan varios hosts en un cluster HA.

        Si un host se cae, las VMs se reinician automáticamente en otros hosts disponibles.

        Se puede configurar con prioridades de arranque.

# ¿Qué es DRS y cómo funciona?

    DRS (Distributed Resource Scheduler) balancea automáticamente la carga de trabajo entre los hosts de un cluster.

    Funcionamiento:

        Monitorea el consumo de CPU y memoria de cada VM.

        Puede mover VMs (con vMotion) de un host a otro para equilibrar recursos.

        Puede configurarse en modo:

            Manual: sugiere migraciones.

            Automático: ejecuta las migraciones sin intervención.

# ¿Qué es Hot Add?

    Función que permite agregar CPU o memoria a una VM en funcionamiento sin necesidad de apagarla.

    Requiere:

        Que esté habilitado en la configuración de la VM.

        Que el sistema operativo invitado lo soporte.

# ¿Qué es un Data Center?

    En VMware vCenter, un Data Center es una unidad lógica de administración que agrupa:

        Hosts ESXi.

        Clusters.

        Máquinas virtuales.

        Almacenamiento (datastores).

        Redes virtuales.

    Sirve para organizar y administrar recursos virtuales de manera centralizada y ordenada.

# ¿Qué es un template en VMware?

    Es una VM preconfigurada que se usa como base para crear otras VMs rápidamente.

# ¿Qué es un cluster en VMware?

    Es un grupo de hosts ESXi que comparten recursos y pueden tener activadas funciones como HA y DRS.

# ¿Cuál es la función de un datastore?

    Es el espacio de almacenamiento donde se guardan los discos virtuales, snapshots, ISOs y archivos de las VMs.

# ¿Qué es Storage vMotion?

    Permite migrar los discos de una VM de un datastore a otro sin apagarla.

# ¿Qué es VM affinity y anti-affinity rules?

    Son reglas que definen:

        Affinity: VMs que deben ejecutarse juntas en el mismo host.

        Anti-affinity: VMs que deben ejecutarse en hosts distintos (por ejemplo, servidores críticos que no conviene que estén en el mismo host).

# ¿Qué harías si un datastore se queda sin espacio?

    Liberar espacio borrando snapshots viejos.

    Expandir el datastore.

    Mover VMs a otro datastore con Storage vMotion.

# ¿Para qué sirven los clusters en VMware?

    Un cluster en VMware es un grupo de hosts ESXi que trabajan juntos como una sola unidad de recursos.

Sirve para:

Agrupar recursos de varios hosts ESXi

    Suma la CPU, RAM y almacenamiento de todos los hosts, permitiendo que las VMs usen los recursos del cluster sin preocuparse en qué host están corriendo.

Habilitar funciones avanzadas como:

    HA (High Availability): reinicia automáticamente las VMs en otro host si uno falla.

    DRS (Distributed Resource Scheduler): balancea las VMs entre los hosts para distribuir la carga de manera automática.

    vMotion y Storage vMotion: permite mover VMs o discos entre hosts y datastores en caliente dentro del cluster.

Simplificar la administración

    Centraliza políticas de recursos, redes, almacenamiento, reglas de afinidad y permisos a nivel cluster.

Escalabilidad

    Podés agregar más hosts al cluster sin interrumpir las operaciones.

Resumen práctico:

Sin cluster:

    Cada host se administra por separado.

    No hay balanceo automático ni alta disponibilidad.

Con cluster:

    Los recursos se comparten.

    Hay balanceo de carga.

    Alta disponibilidad ante fallos.

    Gestión centralizada.

Te la pueden preguntar así:

    ¿Qué beneficios aporta tener un cluster en VMware?

Respuesta simple:

Permite agrupar varios hosts ESXi para compartir recursos, balancear la carga, asegurar alta disponibilidad de las VMs y habilitar funciones como HA, DRS y vMotion de forma centralizada.

# Conceptos complementarios que pueden aparecer:

    Template:
    Una VM base que se guarda como plantilla para clonar nuevas VMs rápidamente.

    Resource Pools:
    Grupos lógicos dentro de un cluster que permiten asignar y limitar recursos (CPU/RAM) a conjuntos de VMs.

    Fault Tolerance (FT):
    Tecnología de alta disponibilidad que permite tener una copia en espejo en tiempo real de una VM en otro host. Si falla, la copia toma el control sin pérdida de servicio ni downtime.
    No se usa tanto como HA, pero es una pregunta de bonus.

    Datastore Cluster (Storage DRS):
    Agrupa varios datastores en un solo pool de almacenamiento, y balancea automáticamente las VMs entre esos datastores según el espacio y la carga.

    Snapshots:
    Aunque ya lo tenías, recordar siempre:
    "Snapshot no es backup", es solo un punto de restauración rápido.

    vSphere Web Client / vSphere Client:
    Interfaz de administración de vCenter y hosts ESXi.

# Conceptos de red muy frecuentes:

    vSwitch (Virtual Switch):
    Es un switch virtual que permite conectar las VMs entre sí y con la red física.

    Port Groups:
    Grupos de configuración de red dentro de un vSwitch que permiten definir políticas de red (VLAN, seguridad, etc.).

# Diferencia entre vSwitch Standard y Distributed

Standard vSwitch (vSS):

    Se configura localmente en cada host ESXi.

    Cada host administra sus propios vSwitches.

    Si tenés 10 hosts, tenés que configurar 10 vSwitches por separado.

    Bueno para entornos chicos o simples.

Ventaja: Fácil de usar, sin necesidad de vCenter.

# Distributed vSwitch (vDS):

    Se configura centralizadamente desde vCenter y se aplica a todos los hosts del cluster.

    Te permite manejar las redes virtuales de forma unificada, sin tener que ir host por host.

    Soporta características más avanzadas (QoS, monitoreo, port mirroring, etc).

Ventaja: Administración más fácil y potente en entornos grandes.

Ejemplo práctico de diferencia:
Si querés agregar un nuevo grupo de puertos para todas tus VMs:

    Con vSS, tenés que ir uno por uno en cada host.

    Con vDS, lo hacés una sola vez desde vCenter y listo, se replica en todos.

# ¿Qué es Fault Tolerance (FT) y para qué se usa?

Fault Tolerance (FT):

    Proporciona alta disponibilidad sin pérdida de servicio ni datos.

    Mantiene una VM secundaria sincronizada en tiempo real con la principal.

    Si el host de la VM principal falla, la VM secundaria toma el control automáticamente.

    No hay pérdida de paquetes ni de estado.
    Ideal para sistemas críticos, como:

        Bases de datos financieras.

        Sistemas de control industrial.

        Servicios médicos.
        
FT On-Demand o "Enhanced FT":

    Podés habilitar FT solo cuando lo necesitás (por ejemplo, durante un mantenimiento planificado o pico de uso).

    Mejora el rendimiento respecto a las versiones anteriores de FT, permitiendo usar más de 1 vCPU.

    Requiere que los hosts estén en un cluster con almacenamiento compartido y vMotion habilitado.

Resumen corto:

    ¿Cuál es la diferencia entre vSwitch estándar y distribuido?

Respuesta:

El vSwitch estándar se configura por separado en cada host ESXi. El vSwitch distribuido se configura desde vCenter y se aplica a todos los hosts del cluster, permitiendo una administración centralizada y funciones avanzadas.

    ¿Qué es Fault Tolerance y cuándo lo usarías?

Respuesta:
Fault Tolerance mantiene una copia exacta de una VM corriendo en otro host. Si el host principal falla, la copia toma el control sin downtime ni pérdida de datos. Se usa en servicios críticos donde ni siquiera unos segundos de caída son aceptables.
