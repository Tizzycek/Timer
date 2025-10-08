#include "mainwindow.h"
#include "timercontroller.h"
#include "ui_mainwindow.h"
#include "mytask.h"
#include <QTimer>
#include <QThread>
#include <QMessageBox>
#include <QRandomGenerator64>
#include <QFile>
#include <QStandardPaths>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(size());

    setWindowTitle("Timer");

    timer = new QTimer(this);

    controller = new TimerController(this);
    connect(controller, &TimerController::tick, this, &MainWindow::updateCountdown);
    connect(controller, &TimerController::finished, this, &MainWindow::stopTimer);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startCountdown);
    connect(ui->actionModifica_configurazioni, &QAction::triggered, this, &MainWindow::modificaConfig);
    connect(ui->actionA_proposito, &QAction::triggered, this, &MainWindow::info);

    ui->hoursSpinBox->setRange(0, 23);
    ui->minutesSpinBox->setRange(0, 59);
    ui->secondsSpinBox->setRange(0, 59);

    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::info(){
    QMessageBox::about(this, "A proposito", "Timer\nVer 2.0\n© Tiziano Ceccon, 2025");
}

void MainWindow::modificaConfig(){
    QString stopPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/config";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Attenzione", "Modificare il file di configurazione in maniera non corretta potrebbe portare a comportamenti imprevisti dell'applicazione: farlo solo se si è utenti esperti.\nSi consiglia di utilizzare percorsi assoluti.\nContinuare?");
    qDebug () << stopPath ;
    if (reply == QMessageBox::Yes)
        QDesktopServices::openUrl(QUrl::fromLocalFile(stopPath));
}

void MainWindow::startCountdown() {
    unsigned hour = ui->hoursSpinBox->value();
    unsigned min = ui->minutesSpinBox->value();
    unsigned sec = ui->secondsSpinBox->value();

    if (min == 0 && sec == 0 && hour == 0) {
        QMessageBox::warning(this, "Errore", "Imposta una durata maggiore di 0.");
        return;
    }

    QString stopPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/stop.flag";

    QMessageBox msgBox;
    msgBox.setWindowTitle("Lo sapevi che...");
    msgBox.setText(randomSentence());
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.button(QMessageBox::Ok)->setText("Andiamo!");
    msgBox.exec();

    qDebug() << stopPath ;
    QFile::remove(stopPath);
    startMyTask();

    controller->calculateTotalSec(hour, min, sec);
    qDebug() << controller->totalSeconds();
    qDebug() << controller->remaining();

    // Imposta progress bar
    ui->progressBar->setMaximum(controller->totalSeconds());


    ui->startButton->setEnabled(false);
    ui->minutesSpinBox->setEnabled(false);
    ui->secondsSpinBox->setEnabled(false);
    ui->hoursSpinBox->setEnabled(false);

    controller->start();

    //timer->start(1000); // ogni secondo

    //controller->update();
}

void MainWindow::stopTimer()
{
    QString stopPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/stop.flag";
    QFile f(stopPath);
    f.open(QIODevice::WriteOnly);
    f.write("stop");
    f.close();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Timer scaduto");
    msgBox.setText("Il nostro tempo è terminato");
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.button(QMessageBox::Ok)->setText("Oh no!");

    msgBox.exec();

    ui->startButton->setEnabled(true);
    ui->minutesSpinBox->setEnabled(true);
    ui->secondsSpinBox->setEnabled(true);
    ui->hoursSpinBox->setEnabled(true);

    ui->progressBar->setValue(0);
    ui->timerLabel->setText("È giunto il momento di decidere la tua scadenza");
}

void MainWindow::updateCountdown(QTime remaining, unsigned elapsed) {
    ui->progressBar->setValue(elapsed);

    ui->timerLabel->setText("Tempo rimanente: " + remaining.toString("hh:mm:ss"));
}


void MainWindow::startMyTask() {
    QThread *thread = new QThread;
    MyTask *task = new MyTask;

    task->moveToThread(thread);

    connect(thread, &QThread::started, task, &MyTask::run);
    connect(task, &QObject::destroyed, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(thread, &QThread::finished, task, &QObject::deleteLater);

    thread->start();

    qDebug() << "[MainWindow] Task avviato su thread separato.";
}

QString MainWindow::randomSentence(){
    QString sentences[] = {
        "Prima della partita è dopo la partita\n(Sepp Herbeger)",
        "La palla è rotonda, il gioco dura 90 minuti, tutto il resto è teoria\n(Sepp Herbeger)",
        "Alice: \"Per quanto tempo è per sempre?\"\nBianconiglio: \"A volte, solo un secondo\"\n(Lewis Carrol)"
        "Sta come un pesce\nche ignora l’oceano\nl’uomo nel tempo.\n(Issa Kobayashi)",
        "Come mai, se il tempo non esiste, noi siamo fatti su schema temporale?\n(Cesare Pavese, Diari)",
        "Il tempo non va misurato in ore e minuti, ma in trasformazioni.\n(Fabrizio Caramagna)",
        "Tra dieci minuti, sono quaranta minuti che mia moglie “tra cinque minuti” è pronta!\n(mamo3pallille, Twitter)",
        "Il tempo è un gioco, giocato splendidamente dai bambini\n(Eraclito)",
        "La cattiva notizia è che il tempo vola. La buona notizia è che sei il pilota.\n(Michael Althsuler)",
        "La cosa più preziosa che puoi ricevere da chi ami è il suo tempo.\nNon sono le parole, non sono i fiori, i regali. È il tempo.\nPerché quello non torna indietro e quello che ha dato a te è solo tuo, non importa se è stata un’ora o una vita.\n(David Grossman)",
        "Nankurunaisa.\nCredo sia una delle parole più belle del mondo.\nE’ giapponese e significa “con il tempo si sistema tutto”.\n(Anonimo)",
        "Il tempo è il mezzo di cui la natura dispone per impedire che le cose avvengano tutte in una volta.\n(John Archibald Wheeler)",
        "Quando un uomo siede vicino ad una ragazza carina per un’ora, sembra che sia passato un minuto. Ma fatelo sedere su una stufa accesa per un minuto e gli sembrerà più lungo di qualsiasi ora. Questa è la relatività.\n(Albert Einstein)",
        "Nella teoria della relatività non esiste un unico tempo assoluto, ma ogni singolo individuo ha una propria personale misura del tempo, che dipende da dove si trova e da come si sta muovendo.\n(Stephen Hawking)",
        "Domenica saremo insieme, cinque, sei ore, troppo poche per parlare, abbastanza per tacere, per tenerci per mano, per guardarci negli occhi.\n(Franz Kafka, Lettere a Milena)",
        "La sera del 14 luglio 1789 (giorno storico della Rivoluzione Francese), Luigi XVI di Francia sul suo diario giornaliero scriveva: “Oggi, niente di nuovo”.\n(Anonimo)",
        "Il tempo è un’illusione.\n(Albert Einstein)",
        "Il tempo fluisce in modo uguale per tutti gli uomini. E ogni uomo galleggia nel tempo in maniera diversa.\n(Manuel Neila)",
        "La bambina si nascose dietro un albero inseguita dalle proprie risate.\nIl signor Tempo si era fermato prima e la guardava da lontano, come chi non avesse più la forza di correrle dietro.\n(Fabrizio Caramagna)",
        "Una volta a Stephen Hawking chiesero: “C’è stato un tempo, prima dell’inizio del tempo?” Rispose: “Man mano che andiamo a ritroso, il tempo si avvicina a raggiungere il niente, ma non è mai stato il niente”.\n(Andrea Pomella)",
        "Il tempo – che gli uomini tentano di domare con gli orologi, fino a renderlo un automa – è per se stesso di natura vaga, imprevedibile e multiforme, tale che ognuno dei suoi punti può assumere la misura dell’atomo o dell’infinito.\n(Elsa Morante)",
        "Che cos’è il tempo? Se nessuno me lo domanda, lo so. Se voglio spiegarlo a chi me lo domanda, non lo so più.\n(Agostino d’Ippona)",
        "I due maggiori tiranni del mondo: il caso e il tempo.\n(Johann Gottfried Herder)",
        "Non rimpiango le persone che ho perso col tempo, ma rimpiango il tempo che ho perso con certe persone, perché le persone non mi appartenevano, gli anni sì.\n(Carl Gustav Jung)",
        "È stato molto tempo fa, e ora non so più nulla di lei che una volta era tutto. Ma tutto passa\n(Bertolt Brecht)",
        "Con alcune persone perdi tempo, con altre perdi la nozione del tempo e con altre recuperi il tempo perduto.\n(martamj32, Twitter)",
        "Un uomo che osa sprecare un’ora del suo tempo non ha scoperto il valore della vita.\n(Charles Darwin)",
        "Affidare l’orologio della propria vita nelle mani di un figlio, in un pomeriggio di giochi: quando lo si riprende è di nuovo luminoso e segna tutti i secondi\n(Fabrizio Caramagna)",
        "Osservo con inatteso distacco il bianco che lentamente sta passando dalla barba ai capelli. Non mi ha mai spaventato il tempo, ma la possibilità di sprecarlo.\n(orporick, Twitter)",
        "Nella corsia del tempo non si può sorpassare né fare inversioni a U.\n(Edoardo Boncinelli)",
        "Mai prima d’ora abbiamo avuto così poco tempo per fare così tanto.\n(Franklin Delano Roosevelt)",
        "L’uomo vive nel tempo, nella successione del tempo, e il magico animale nell’attualità, nell’eternità costante.\n(Jorge Luis Borges)",
        "Il tempo è buon amico, il tempo è buon testimone, il tempo è denaro, il tempo è galantuomo, il tempo è gran medico, il tempo è una lima sorda, il tempo consuma ogni cosa, il tempo vola, ma nessuno ha veramente capito a cosa serva il tempo.\n(Fabrizio Caramagna)",
        "Voi occidentali, avete l’ora ma non avete mai il tempo.\n(Gandhi)",
        "Gli occidentali indossano al polso i loro dèi.\n(Vimalanda)",
        "Riparate la ruota del mondo! Perché deve continuamente girare? Dove si trova la retromarcia?\n(Jack London)",
        "Il tempo è come un fiocco di neve, scompare mentre cerchiamo di decidere che cosa farne.\n(Romano Battaglia)",
        "Il tempo è ciò che più desideriamo, ma che, ahimè, peggio usiamo.\n(William Penn)",
        "Il tempo è spesso puntuale nel farci capire molte cose in ritardo.\n(Guido Rojetti)",
        "Il tempo è la moneta della tua vita. E’ l’unica che possiedi e che puoi decidere come spendere. Stai attento non permettere ad altri di usarla al tuo posto\n(Carl Sandburg)",
        "Che sia il migliore o il peggiore dei tempi, è il solo tempo che abbiamo.\n(Art Buchwald)",
        "Amore non soggiace al tempo…\nAmore non muta in brevi ore e settimane,\nma impavido resiste fino al giorno del Giudizio.\n(William Shakespeare)",
        "La più grossa dimostrazione d’amore è il tempo dedicato, il resto sono parole.\n(Anonimo)",
        "È il tempo che hai perduto per la tua rosa che ha reso la tua rosa così importante.\n(Antoine de Saint-Exupéry)",
        "La vita non è altro che un brutto quarto d’ora, composto da attimi squisiti.\n(Oscar Wilde)",
        "La farfalla non conta mesi ma momenti, e ha tempo a sufficienza.\n(Rabindranath Tagore)",
        "Non so come sono chiamati gli spazi tra i secondi ma è in quegli spazi che il dolore picchia più forte quando si sente la mancanza di una persona.\n(Fabrizio Caramagna)",
        "Non dire che non hai abbastanza tempo. Hai esattamente lo stesso numero di ore in una giornata che è stato dato a Michelangelo, Pasteur, Madre Teresa, Leonardo da Vinci, Thomas Jefferson e Albert Einstein.\n(H. Jackson Brown, Jr)",
        "Il tempo. Il più grande e il più antico di tutti i tessitori. Ma la sua fabbrica è un luogo segreto, il suo lavoro silenzioso, le sue mani mute.\n(Charles Dickens)",
        "Il tempo passa, dici? Ah, no! Ahimè, il tempo resta, noi passiamo.\n(Henry Austin Dobson)",
        "Oggi il tempo è passato dappertutto, nelle stanze, nelle strade, negli alberi. L’unico posto dove non è passato è in quella nuvola lassù nel tramonto, che mi chiama allo stesso modo di vent’anni fa.\n(Fabrizio Caramagna)",
        "Quanto dura un minuto, dipende da quale lato della porta del bagno si è.\n(Arthur Bloch, La seconda legge di Zall)",
        "Il tempo non ha nessuna divisione visibile che ne segni il passaggio, non una tempesta con tuoni, né squilli di tromba che annuncino l’inizio di un nuovo mese o un nuovo anno. Persino quando inizia un nuovo secolo siamo solo noi mortali che suoniamo le campane e spariamo in aria con le pistole.\n(Thomas Mann)",
        "Il tempo è troppo lento per coloro che aspettano, troppo rapido per coloro che temono, troppo lungo per coloro che soffrono, troppo breve per coloro che gioiscono, ma per coloro che amano il tempo è eternità.\n(Henry van Dyke)",
        "S’è fatto tardi molto presto.\n(Dr Seuss)",
        "Il tempo scorre lentamente con una velocità impressionante.\n(Pino Caruso)",
        "Il futuro è qualcosa che raggiunge tutti alla velocità di sessanta minuti l’ora, qualunque cosa tu faccia, chiunque tu sia.\n(CS Lewis)",
        "Quando si lotta contro il momento presente, in realtà si lotta contro l’intero universo.\n(Deepak Chopra)",
        "Tra gli atti di sparizione, nulla supera ciò che succede alle otto ore che presumibilmente ci rimangono dopo le otto ore di sonno e le otto di lavoro.\n(Doug Larson)",
        "L’orologio parlava ad alta voce. L’ho buttato via, mi faceva paura quello che diceva.\n(Tillie Olsen)",
        "Sarebbe bello riuscire a riempire almeno un giorno. Riempirlo di opere e brividi e dettagli, senza lasciare fuori neanche un minuto o un secondo.\nChissà come tremerebbe il tempo a vederci così forti.\n(Fabrizio Caramagna)",
        "In uno di questi giorni l’uomo viaggerà alla velocità della luce, ma questo interessa poco a chi come noi sta ancora cercando di raggiungere la velocità del tempo.\n(Robert Brault)",
        "Abbiamo tutti le nostre macchine del tempo. Alcune ci riportano indietro, e si chiamano ricordi. Alcune ci portano avanti, e si chiamano sogni.\n(Jeremy Irons)",
        "Il fiore che tieni nelle tue mani è nato oggi e ha già la tua età.\n(Antonio Porchia)",
        "Il tempo è come un fiume: non risale mai alla sorgente.\n(Conte di Rivarol)",
        "Il paradosso del donare il proprio tempo a un altro:\nregali un pezzo della tua vita che non sarà più tuo,\nma che proprio per questo non andrà perduto.\n(Fabrizio Caramagna)",
        "Gli anni come grandi buoi neri percorrono il mondo\nE Dio, il pastore, li spinge da dietro.\n(William Butler Yeats)",
        "Se il tempo fosse soltanto oro…, potresti anche permetterti di perderlo. Ma il tempo è vita, e tu non sai quanta te ne resta.\n(San Josemaria Escrivà de Balaguer)",
        "Il tempo è più prezioso del denaro. Puoi fare più denaro, ma non puoi avere più tempo.\n(Jim Rohn)",
        "Il tempo raffredda, il tempo chiarifica; nessuno stato d’animo si può mantenere del tutto inalterato nello scorrere delle ore.\n(Thomas Mann)",
        "La vita porta via troppo tempo agli uomini.\n(Stanislaw Jerzy Lec)",
        "Che cosa non mi piace della morte? Forse l’ora.\n(Woody Allen)",
        "Nell’Apocalisse l’angelo giura che il tempo non esisterà più. È molto giusto, preciso, esatto. Quando tutto l’uomo raggiungerà la felicità, il tempo non esisterà più, perché non ce ne sarà più bisogno. È un’idea giustissima. Dove lo nasconderanno? Non lo nasconderanno in nessun posto. Il tempo non è un oggetto, è un’idea. Si spegnerà nella mente\n(Fëdor Dostoevskij)",
        "Se si potesse dare in elemosina tutto il tempo sciupato, moltissimi mendicanti sarebbero ricchi.\n(Carmen Sylva)",
        "Mi piacerebbe stare all’angolo di una strada molto frequentata, con il cappello in mano, e pregare la gente di buttarmi tutte le ore che hanno sprecato.\n(Bernard Berenson)",
        "Perdi i tuoi soldi e hai perso solo i tuoi soldi, ma perdi tempo e hai perso una parte della tua vita.\n(Michael Leboeuf)",
        "Il tempo perduto è come un buco in un calzino. Diventa sempre peggio.\n(Anne Lindbergh)",
        "Rimpiangere il tempo sprecato è ulteriore tempo sprecato.\n(Mason Cooley)",
        "Quando mi viene chiesto da quanto sono io qui, io rispondo “Un secondo…” o “Un giorno…” o “Un secolo”. Tutto dipende da che cosa io intendo per “qui…” e “io…” e “sono”.\n(Samuel Beckett)",
        "Il tempo è morto fintanto che è scandito da piccoli ingranaggi. Solo quando l’orologio si ferma il tempo prende vita.\n(William Faulkner)",
        "Non abbiamo tempo per dedicarci un po’ di tempo.\n(Eugène Ionesco)",
        "Noi passiamo la nostra vita a correre: ci alziamo con la sveglia, mangiamo e dormiamo con l’occhio all’orologio, andiamo a lavorare e finalmente la pensione. E cosa ci danno? Un orologio.\n(Dave Allen)",
        "Lavorando accaniti il tempo passa via e non lo vedi. Per vivere a lungo bisogna annoiarsi.\n(Fausto Melotti)",
        "Domani è spesso il giorno più occupato della settimana.\n(Proverbio spagnolo)",
        "Non limitarti a segnare il tempo; usa il tempo per lasciare il tuo segno.\n(Harvey B. Mackay)",
        "Ti raccomando di avere cura dei minuti, e le ore avranno cura di se stesse.\n(IV° Conte di Chesterfield)",
        "Ogni secondo è di valore infinito, perché è il rappresentante di un’eternità tutta intera.\n(Goethe)",
        "Il tempo, sulla meridiana solare, si ferma cortesemente un attimo per lasciare passare una nuvola.\n(Enrique Baltanas)",
        "Le mie particelle di tempo giocano con l’eternità.\n(Antonio Porchia)",
        "Mi è sempre sembrato piuttosto bizzarro il fatto che dovremmo fare la fila per vendere il nostro tempo a qualcun altro. È una forma di schiavitù, schiavitù volontaria. Noi pensiamo che sia una grossa cosa, ma è una follia.\n(Charles Handy)",
        "Il tempo, a volte, sembra che non passi, è come una rondine che fa il nido sulla grondaia, esce ed entra, va e viene, ma sempre sotto i nostri occhi.\n(José Saramago)",
        "L’età, nel suo scorrere, mi libera dalla necessità dello spazio e mi fa cadere schiavo del tempo.\n(Mircea Oprea)",
        "Tutti gli oggetti dei sensi, cadono nel tempo e stanno necessariamente fra di loro in rapporti di tempo.\n(Immanuel Kant)",
        "L’acqua che tocchi de’ fiumi è l’ultima di quelle che andò e la prima di quella che viene. Così il tempo presente.\n(Leonardo da Vinci)",
        "Il tempo è un grande maestro. Peccato che uccida tutti i suoi allievi.\n(Hector Berlioz)",
        "Gli uomini parlano di ammazzare il tempo, mentre il tempo li ammazza in silenzio.\n(Dion Boucicault)",
        "In realtà, ammazzare il tempo è solo il nome di un altro dei molteplici modi con cui Il tempo ci uccide.\n(Osbert Sitwell)",
        "Al tempo… non tremano mai le mani. Muove lentamente il bisturi sui nostri volti, come un assassino seriale innamorato dalla sua arte.\n(Jonut Caragea)",
        "È soprattutto quando le giornate sembrano lunghe che gli anni passano in fretta.\n(Alfred Capus)",
        "Quando arriva il tempo in cui si potrebbe, è passato quello in cui si può.\n(Marie von Ebner-Eschenbach)",
        "Cosa sono i millenni? Un manciata di tempo. Polvere in confronto a un unico sguardo dell’eternità.\n(Hermann Hesse)",
        "La gente comune si preoccupa unicamente di passare il tempo; chi ha un qualche talento pensa invece a utilizzarlo.\n(Arthur Schopenhauer)",
        "Molto può essere fatto con quei piccoli pezzi e brandelli di tempo che ogni giorno vengono prodotti, e che la maggior parte degli uomini getta via.\n(Charles Caleb Colton)",
        "Giorno, n. Un periodo di ventiquattro ore, in gran parte sprecate.\n(Ambrose Bierce)",
        "C’è un tipo di ladro che la legge non punisce e che ruba ciò che è più prezioso per gli uomini: il tempo.\n(Napoleone Bonaparte)",
        "Posso perdere una battaglia, ma non perderò mai un minuto.\n(Napoleone Bonaparte)",
        "Nella modalità dell’avere, il tempo diviene il nostro dominatore. Nella modalità dell’essere, il tempo è detronizzato, cessa di essere l’idolo che governa la nostra vita. Nella società industriale, il tempo domina sovrano.\n(Erich Fromm)",
        "Il tempo non esiste, è solo una dimensione dell’anima. Il passato non esiste in quanto non è più, il futuro non esiste in quanto deve ancora essere, e il presente è solo un istante inesistente di separazione tra passato e futuro.\n(Sant’Agostino)",
        "Il presente, come il punto, non è un entità quantificabile. Essendo inconsistente è un’ astratta unità del pensiero. Il passato è il nostro maestro, il futuro il nostro esaminatore. Chi vive del presente fonda la sua esistenza su di un’illusione.\n(Bertrand Russel)",
        "Il tempo è un assassino e porta via con sé ogni nostro secondo. E ha sempre un alibi. Lui non c’era dove eravamo noi, esisteva in qualche altro luogo\n(Fabrizio Caramagna)",
        "Il tempo si muove in una direzione, i ricordi in un’altra.\n(William Gibson)",
        "Il tempo è un grande medico.\n(Benjamin Disraeli)",
        "Il tempo cura, lo spazio ferisce\n(orporick, Twitter)",
        "Il tempo è una sarta specializzata in riparazioni.\n(Faith Baldwin)",
        "Il tempo! il correttore quando i nostri giudizi sbagliano.\n(Lord Byron)",
        "Il tempo divora ogni cosa – Tempus edax rerum.\n(Proverbio latino)",
        "Dopo averti tradito, il tempo conta le sue monete d’argento nei tuoi capelli.\n(Nicolae Petrescu Redi)",
        "Ogni anno oltrepassiamo senza saperlo il giorno della nostra morte.\n(Valeriu Butulescu)",
        "Gli orologi sono rispetto al tempo ciò che un dizionario è rispetto al linguaggio.\n(Jordi Doce)",
        "In un minuto c’è il tempo per decisioni e scelte che il minuto successivo rovescerà.\n(Thomas Stearns Eliot)",
        "Il tempo è il mezzo per essere che viene offerto a tutto ciò che sarà affinché non sia più.\n(Paul Claudel)",
        "Si avvicina all’essenza del Tempo soltanto chi sa sprecarlo. L’uomo di nessuna utilità.\n(EM Cioran)",
        "Il tempo spreca i nostri corpi e il nostro ingegno, ma perde tempo, quindi siamo pari.\n(Anonimo)",
        "Il tempo è il fuoco in cui bruciamo.\n(Delmore Schwartz)",
        "Non ho mai capito perché noi esseri umani pensiamo al tempo come a una linea che va da dietro in avanti, mentre potrebbe procedere in tutte le direzioni, come ogni altra cosa nel sistema del mondo.\n(Ferruccio Busoni)",
        "Per secoli, l’uomo ha creduto che il sole girasse intorno alla terra. Secoli dopo, pensa ancora che il tempo si muova in senso orario.\n(Robert Brault)",
        "Ti devono aver messo in guardia contro il lasciare scorrere via le ore dorate; ma alcune di quelle ore sono dorate solo perché le lasciamo scorrere via.\n(Sir James Matthew Barrie)",
        "Il tempo c’insegna tante cose, meno come farne buon uso.\n(Roberto Gervaso)",
        "Non è vero che abbiamo poco tempo: la verità è che ne perdiamo molto.\n(Seneca)",
        "L’arte esiste perché la vita non ha tempo sufficiente per essere vissuta.\n(Juan Varo Zafra)",
        "La Gioconda sorride a tutti. Soprattutto al tempo.\n(Vasile Ghica)",
        "Mentre parliamo il tempo, invidioso, sarà già fuggito. Godi il giorno, confidando meno che puoi nel domani.\n(Quinto Orazio Flacco)",
        "Stare con te o stare senza di te è l’unico modo che ho per misurare il tempo.\n(Jorge Luis Borges)",
        "In campagna, il tempo è più integro: passa tramite meno orologi…\n(Efim Tarlapan)",
        "Il tempo è uno strumento sul quale solo Dio sa suonare.\n(Constantin Stoica)",
        "Il tempo è gratis ma è senza prezzo.\nNon puoi possederlo ma puoi usarlo.\nNon puoi conservarlo ma puoi spenderlo.\nUna volta che l’hai perso non puoi più averlo indietro.\n(Harvey MacKay)"
    };

    return sentences[QRandomGenerator::global()->bounded(0,134)];
    //std::seed_seq sseq(0, 101);
    //QRandomGenerator generator(sseq);
}
