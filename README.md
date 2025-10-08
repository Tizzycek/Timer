# Timer
Un timer che fa trascorrere l'attesa senza noia

## Prefazione

> Questa sezione descrive come è nata l'idea del progetto. Per la parte più tecnica, proseguire avanti.

### Attesa e scadere del tempo

Che cos'è un'**attesa**? \
È una frazione di tempo che trascorre fino al suo scadere.

E allora, che cos'è lo **scadere del tempo**? \
*Può sembrare banale, ma chi si è fermato davvero a chiederselo?* \
Lo scadere del tempo è il momento in cui il periodo prestabilito termina, facendo venir meno la possibilità di agire o proseguire oltre quel limite.

Cosa dice *Seneca* sull'attesa?
Il maggior ostacolo alla vita è proprio l'attesa: **fa dipendere tutto dal domani e, intanto, sciupa l'oggi**.

Ed è proprio lo scadere del tempo che delinea il confine separante l'attesa dall'evento.

Abbiamo mai pensato a quante attese siamo sottoposti ogni giorno? Abbiamo mai pensato a quante scadenze dobbiamo gestire?

Ma la vera domanda è: chi si è mai fermato ad analizzare come trarre vantaggio dall’attesa, prima che arrivi l’evento che ne segnerà la fine?

### Le fatalità

> Il seguente esempio è ispirato ad alcuni fatti di cronaca risalenti circa a metà aprile 2025. Esso non mira e non vuole in nessun modo ostentare la criticità della situazione, ma serve esclusivamente a narrare un punto di vista su questo tema.
> È infatti tratto da alcune riflessioni personali fatte durante quel periodo, delineanti la mia situazione del momento.

Immaginate la gente che abita nella zona dei campi flegrei. Essa sa di essere condannata, perché, prima o poi, il mondo sotto a lei inizierà a esplodere tragicamente.

Loro sanno che, quando sarà il momento, non ci sarà scampo. Ed è solo una questione di tempo prima che si verifichi.

Allora, la domanda che avrebbe senso porsi, è: **come si potrebbe sfruttare il tempo a proprio vantaggio sapendo di essere condannati**?

Dal mio punto di vista, occorre sfruttare al massimo il tempo che ci è stato concesso. Il **come** è personale, ma **farlo** è ***necessario***. Il contrario significherebbe **buttare via** un'opportunità che è stata donata, **sprecandola**.

Riassumiamo. Siamo condannati in una situazione irrimediabile, ma ci è stata donata l'opportunità di fare qualcosa prima che sia troppo tardi.
Come trascorriamo il tempo rimastoci a disposizione?

### Freud e la scrittura

Se siete arrivati fino a qua, molto probabilmente vi starete chiedendo: cosa c'entra tutta questa discussione con la programmazione?

Il discorso precedente acquista senso tramite la conoscenza di alcuni fattori personali. Le argomentazioni precedenti sono state trovate dopo un periodo di vita pieno di progetti da portare a termine, lavori da concludere entro scadenze precise, e gente a cui vuoi bene che sta per sparire.

Se si è soli, avere tutte queste emozioni dentro che si fondono è disturbante.

*Sigmund Freud*, celeberrimo medico neurologo e fondatore della psicoanalisi, sosteneva che la scrittura fosse uno degli elementi fondamentali per l'accesso all'inconscio.
Questa teoria ha mostrato come la scrittura possa descrivere in modo dettagliato i processi mentali.

Quale migliore occasione per farlo? E quale migliore occasione per farlo in `C`?

### L'idea principale

Considerata tutta questa premessa, l'idea ora viene naturalmente da sé.

In ambito informatico, come si può conciliare un'attesa a un destino ineluttabile, sfruttando al meglio il tempo rimanente?

Di base, partiremo creando un'applicazione fungente da timer. \
Semplice, banale. \
Il tempo che abbiamo a disposizione, inserito nell'applicazione, che ci mostra man mano quanto ci rimane.

Ora passiamo alla parte più complessa da ideare. Come sfruttare al meglio il tempo a nostra disposizione?

### Come affrontiamo il decorrere del tempo?

Per passare al meglio quello che mi stava capitando, sono stato in parecchie discoteche.

In alcune sale da ballo, oltre alla musica e alle luci stroboscopiche, si può trovare un elemento bizzarro: \
Schermi con video casuali.

Letteralmente, video casuali. Che senso ha, nel mezzo di una serata techno, mostrare la vita nel Regno Unito durante gli anni '60?

Sinceramente, non ne ho idea. Ma mi è piaciuta così tanto che l'ho voluta implementare nel mio progetto.

Perché fare un semplice timer quando si può creare un timer che, durante la sua esecuzione, mostra video a caso per riempire il tempo?

### Perché un riproduttore di video in ASCII?

L'intenzione ora è chiara. Vogliamo un timer che, durante l'attesa alla sua fine, sfrutti il tempo a sua disposizione per mostrarci dei video.

Tutti abbiamo un computer. Tutti abbiamo un telefono. E penso che sia scontato dire che tutti noi, almeno una volta al giorno, riproduciamo un video sul nostro dispositivo elettronico.

Che banalità sarebbe mostrare dei video normalmente?

Ma noi non abbiamo solo un computer. Abbiamo un computer e sappiamo programmare in `C`. Si può guardare un video dal terminale?

Ovviamente no. È qui che, in nostro soccorso, arriva l'arte ASCII. Convertiamo i nostri video casuali in formato ASCII e avremo l'opportunità di fare qualcosa di più del normale: un riproduttore di video in ASCII.

### Conclusione

Siamo arrivati alla fine del nostro racconto. Il progetto c'è: ora rimane solamente lo sviluppo. 

Chi avrà letto tutta questa parte, si sarà fatto una sua idea.

Sono il primo a dire che il progetto, come le idee dietro, sembrano alquanto assurdi. Eppure, tutto ciò, rappresenta una parte della mia vita, che ho sentito di dover esprimere così.

Il mondo continuerà a girare indifferente? Sarò riuscito ad aiutare qualcuno in una condizione come la mia?  Questo non lo posso sapere. Ma sento in me di aver fatto una cosa più che giusta.

Nel nostro mondo, tutto è destinato a cessare. Basti pensare a ogni singola giornata: ha un inizio, e una fine. 

È il modo in cui la si trascorre che può fare la differenza. Tanto si arriverà al tramonto, ma intanto la si può sfruttare al meglio. E non vale la pena viverla da arrabbiati o tristi... Anche perché siamo più belli quando ridiamo.  

E che poi, alla fine, cos'è un tramonto? \
**Un tramonto è la prova che anche lo scadere del tempo può essere un momento meraviglioso.**

## Struttura e framework

Come framework per comporre tutto è stato utilizzato `Qt`. 

Per quanto riguarda invece il riproduttore di video in ASCII, è stato riutilizzato, riadattandolo ove necessario, il codice di [ASCIIVideoPlayer](https://github.com/Tizzycek/ASCIIVideoPlayer).

### Classi principali

Il programma è composto da 3 classi principali:

- Una classe per la gestione della finestra principale;
- Una classe per la gestione della logica del timer;
- Una classe per la gestione di ASCIIVideoPlayer.

#### Finestra principale

La classe della finestra principale `mainwindow` si occupa della gestione del programma. Crea infatti l'oggetto che si occuperà della logica del timer nel suo costruttore, e inizializza tutti gli elementi.

Gli elementi che compongono la finestra sono:

- Un'etichetta che descrive in brevissimo l'applicazione, e che mostrerà l'avanzamento del conto alla rovescia alla sua partenza;
- `SpinBox` per impostare la durata del timer
  - La durata massima programmabile è 23 ore, 59 minuti e 59 secondi;
- `ProgressBar` che mostra l'avanzamento del timer;
- Menù a tenda per mostrare alcune opzioni, tra cui:
  - Un pulsante che apre il file per le configurazioni di *ASCIIVideoPlayer*;
  - Un pulsante per mostrare le informazioni sull'applicazione;
- Un pulsante principale per avviare il conto alla rovescia.

Prima dell'avvio del timer viene mostrata una frase, parte di una raccolta di aforismi e citazioni sul tempo. \
Attualmente le proposizioni sono 134, e vengono scelte in maniera casuale al click sul pulsante per avviare il timer.

#### Controllo del timer

La classe di controllo del timer `timercontroller` è una classe piuttosto tecnica.

Contiene infatti gli strumenti per la gestione del tempo, il calcolo dei secondi totali, e di quelli rimanenti.

Interagisce con la classe principale tramite dei segnali, invocati con `emit`. 

#### Gestione di ASCIIVideoPlayer

La classe `mytask` si occupa di lanciare *ASCIIVideoPlayer*.

Il suo funzionamento è molto semplice: chiama il terminale che si occupa di chiamare l'eseguibile dell'applicazione. 

La scelta di questa modalità è spiegata nel paragrafo successivo. 

### ASCIIVideoPlayer come applicazione esterna

Per quanto riguarda le interfacce grafiche, in precedenza ho lavorato con `Java Swing`. 

Questo framework permette di avere in esecuzione le applicazioni sia da terminale sia da interfaccia grafica per utente. Senza informarmi troppo, il pensiero è stato di utilizzare Qt allo stesso modo, cercando di avviare il riproduttore di video in caratteri ASCII direttamente dallo stesso terminale.

È quindi iniziato il processo di integrazione del codice già esistente nel codice globale. \
Durante alcuni test ho verificato che, in modalità di debug, funzionava effettivamente. A mio malgrado ho però scoperto che Qt ordinariamente non visualizza l'esecuzione in terminale, ma lo termina ed esegue solamente l'interfaccia grafica.

Si è quindi resa necessaria la separazione delle due applicazioni. 

#### Riadattamento di ASCIIVideoPlayer

Come premesso, il codice di ASCIIVideoPlayer è esterno. 

Esso differisce dalla versione originale attraverso i seguenti punti:

- Nella versione definitiva, il file di configurazione non è più nella stessa cartella dell'eseguibile, ma in una directory nello spazio utente;
- I thread che gestiscono audio e video vengono lanciati di continuo al loro termine;
- Un terzo thread controlla continuamente l'esistenza di un file `stop.flag`, segnale di terminazione del programma. Al suo esito positivo, imposta una variabile globale di controllo che sarà letta dai due thread che concluderanno la loro esecuzione, terminando il programma.

#### Lancio dell'eseguibile

La classe `MyTask` provvede a chiamare il terminale che chiamerà a sua volta l'eseguibile di ASCIIVideoPlayer. 

È formata dal metodo `run()`, che si occupa di lanciare il terminale con comando di chiusura a fine esecuzione. 

Controlla il successo dell'operazione e termina. 

Una volta lanciato, l'eseguibile è completamente indipendente dal framework principale. 

Allo scadere del tempo, il gestore del timer creerà un file `stop.flag`, vuoto ma indicante ad ASCIIVideoPlayer la terminazione della sua esecuzione. 

#### Differenza tra Debug e Release

- Nella versione di **Debug**, il codice di ASCIIVideoPlayer prevede che il file delle configurazioni sia nella stessa directory da cui viene lanciato l'eseguibile.
- Nella versione di **Release**, il codice di _ASCIIVideoPlayer_ prevede che il file delle configurazioni sia nella cartella finale in cui sarà presente dopo l'installazione, ovvero la directory delle informazioni del programma salvate nello spazio utente (la stessa directory in cui apparirà il file `stop.flag`).

#### Piccolo problema in fase di test

Durante la fase di test, è emerso un piccolo problema.

In caso di avvio dell'applicazione in modalità release direttamente da `Qt Creator`, *ASCIIVideoPlayer* potrebbe non essere lanciato. 

Basterà testare il tutto lanciando l'eseguibile direttamente dalla cartella, e dovrebbe essere eseguito tutto correttamente.

## Installazione

L'installazione è molto semplice, in quanto è sufficiente scaricare la _release_ e seguire la procedura automatizzata.

> Alla richiesta dei permessi di amministratore, potrebbe essere notificato che l'applicazione non è sicura. Questo è normale, in quanto sprovvista di firma digitale.
> 
> In ogni caso, la versione è la stessa che vedete pubblicata su GitHub. Se non vi fidaste, potreste provare a compilarla voi stessi.

### Configurazione per Windows di InnoSetup

Per distribuire l'applicazione e permettere l'installazione agli utenti finali, è stato utilizzato `InnoSetup`.

Il file di configurazione si trova nella cartella di release. Provvede a:
- copiare l'eseguibile e tutte le sue dipendenze;
- creare, durante l'installazione, una cartella locale per il file delle configurazioni. 

Ovviamente, prima di configurare il file, è opportuno testare il funzionamento del codice, prestando attenzione all'inclusione di tutte le dipendenze necessarie per il corretto funzionamento dell'applicazione. 