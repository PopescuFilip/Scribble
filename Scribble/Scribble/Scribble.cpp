#include "Scribble.h"
#include "JoinRoom.h"
#include <thread>

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> result;
    size_t startIndex = 0;

    for (size_t found = str.find(delim); found != std::string::npos; found = str.find(delim, startIndex))
    {
        result.emplace_back(str.begin() + startIndex, str.begin() + found);
        startIndex = found + delim.size();
    }
    if (startIndex != str.size())
        result.emplace_back(str.begin() + startIndex, str.end());
    return result;
}

Scribble::Scribble(int username, std::string roomCode, QWidget *parent)
    : QMainWindow{ parent },
    m_isDrawing{ false },
    m_canDraw{ false },
    m_guessedCorrectly{ false },
    m_userId{ username },
      m_roomCode{ roomCode },
    m_drawingArea{ QPoint(90, 130), QPoint(1190, 600) }
{
    ui.setupUi(this);
    ui.textEditPlayersScore->setReadOnly(true);
    ui.Word->setReadOnly(true);

    m_refreshTimer = new QTimer(this);

    setAttribute(Qt::WA_DeleteOnClose);
    QPixmap background("Images/ScribbleBackground.png");
    background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    setPalette(palette);

    setFixedSize(1280, 720);
    setGeometry(140, 70, 2560, 1440);

    connect(ui.ClearWindowButton, SIGNAL(clicked()), this, SLOT(clearWindow()));
    QObject::connect(ui.sendButton, &QPushButton::clicked, this, &Scribble::guessWord);
    QObject::connect(m_refreshTimer, &QTimer::timeout, this, &Scribble::refresh);

    m_refreshTimer->setInterval(3000);
    //m_refreshTimer->start();
    refresh();
}

Scribble::~Scribble()
{}

void Scribble::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "mouse press";
    if (!m_canDraw)
        return;
    m_isDrawing = true;
    m_lastDrawnPoint = { event->pos().x(), event->pos().y() };
    update();
}

void Scribble::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_canDraw)
        return;
    if (!m_isDrawing)
        return;
    if (!IsInDrawingFrame(event->pos()))
    {
        qDebug() << event->pos() << " outside";
        m_isDrawing = false;
        return;
    }
    qDebug() << event->pos() << " inside";
    Coordinate newPoint { event->pos().x(), event->pos().y() };
    m_drawing.push_back({ m_lastDrawnPoint,newPoint });
    m_lastDrawnPoint = { event->pos().x(), event->pos().y() };
    update();
}

void Scribble::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << "mouse release";
    m_isDrawing = false;
}

void Scribble::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(kBrushSize);
    painter.setPen(pen);
    for (const auto& line : m_drawing)
        painter.drawLine(line.first.first, line.first.second, line.second.first, line.second.second);
}

std::string Scribble::DrawingToString()
{
    std::stringstream ss;
    for (size_t i = 0; i < m_drawing.size(); ++i)
    {
        const auto& [firstPoint, secondPoint] = m_drawing[i];
        const auto& [firstX, firstY] = firstPoint;
        const auto& [secondX, secondY] = secondPoint;
        
        ss << firstX << " " << firstY << " " << secondX << " " << secondY;
        if (i == m_drawing.size() - 1)
            break;
        ss << ",";
    }
    return ss.str();
}

void Scribble::SetDrawingFromString(const std::string& string)
{
    m_drawing.clear();
    for (const auto& kvStr : split(string, ","))
    {
        const auto& kvVector{ std::move(split(kvStr, " ")) };

        if (kvVector.size() != 4)
            break;

        const int& firstX{ std::stoi(kvVector[0]) };
        const int& firstY{ std::stoi(kvVector[1]) };
        const int& secondX{ std::stoi(kvVector[2]) };
        const int& secondY{ std::stoi(kvVector[3]) };

        m_drawing.push_back({ { firstX, firstY }, { secondX, secondY } });
    }
}

bool Scribble::IsInDrawingFrame(const QPoint& point)
{
    qDebug() << point << " check " << m_drawingArea;
    return m_drawingArea.contains(point);
}

void Scribble::ThreadedPutDrawingToServer()
{
    auto SendDrawingToServer = [&](const int userId, const std::string roomCode)
        {
            cpr::Response response{ PutDrawing(userId,roomCode,DrawingToString()) }; 

        };
    std::thread pushDrawingThread(SendDrawingToServer, m_userId, m_roomCode);
    pushDrawingThread.detach();
}

void Scribble::ShowPlayers()
{
    cpr::Response response{ GetPlayers(m_roomCode) };

    if (response.status_code != 200)
    {
        QMessageBox::critical(this, "Error", "something went wrong");
        return;
    }

    std::stringstream ss;
    auto players = crow::json::load(response.text);
    for (const auto& player : players)
    {
        ss << player["name"].s() << " " << player["score"].i() << "\n";
    }
    ui.textEditPlayersScore->setReadOnly(false);
    ui.textEditPlayersScore->setPlainText(QString::fromUtf8(ss.str().c_str()));
    ui.textEditPlayersScore->setReadOnly(true);
}

void Scribble::ShowWord()
{
    cpr::Response response{ GetWord(m_userId, m_roomCode) };

    if (response.status_code != 200)
    {
        QMessageBox::critical(this, "Error", "something went wrong");
        return;
    }

    std::string word{ response.text };

    ui.Word->setReadOnly(false);
    ui.Word->setPlainText(QString::fromUtf8(word.c_str()));
    ui.Word->setReadOnly(true);
}

void Scribble::refresh()
{
    m_refreshTimer->stop();

    cpr::Response response{ CheckState(m_userId,m_roomCode) }; 

    if (response.status_code != 200)
        return;

    auto json = crow::json::load(response.text);


    if (json["code"].i() == 404)
    {
        QMessageBox::critical(this, "Error", "game room is gone");
        return;
    }

    std::string gameStateString{ json["gameState"].s() };
    GameState gameState{ GetGameStateFromString(std::move(gameStateString)) };
    if (gameState == GameState::Ended)
    {
        close();
        EndScreen* endScreen = new EndScreen(m_roomCode);
        endScreen->show();
        return;
    }

    if (gameState == GameState::BetweenRounds)
    {
        m_canDraw = false;
        m_guessedCorrectly = false;
        ShowPlayers();
        m_drawing.clear();
        m_refreshTimer->start();
        return;
    }
    ShowWord();
    m_canDraw = json["canDraw"].b();
    
    if (m_canDraw)
        ThreadedPutDrawingToServer();
    else
    {
        std::shared_ptr<std::string> sp = std::make_shared<std::string>(json["drawing"].s());
        auto SetDrawing = [&](const std::string& drawing)
            {
                SetDrawingFromString(drawing);
            };
        std::thread setThread(SetDrawing, *sp);
        setThread.detach();
    }
    //SetDrawingFromString(json["drawing"].s());
    m_refreshTimer->start();
}

void Scribble::guessWord()
{
    std::string word{ ui.chatlineEdit->text().toUtf8().constData() };
    ui.chatlineEdit->clear();

    if (m_canDraw)
    {
        QMessageBox::information(this, "Info", "you are the painter, you can't guess");
        return;
    }

    if (m_guessedCorrectly)
    {
        QMessageBox::information(this, "Info", "you have already guessed correctly");
        return;
    }

    cpr::Response response{ GuessWord(m_userId, m_roomCode, word) };

    if (response.status_code != 200)
    {
        QMessageBox::critical(this, "Error", "game room is gone");
        return;
    }
     
    if (response.text == "correct")
    {
        m_guessedCorrectly = true;
        QMessageBox::information(this, "Congrats!!", "you have guessed correctly");
        return;
    }
    
    QMessageBox::information(this, "Incorrect", "unfortunately that's not the word");
}


void Scribble::clearWindow()
{
    if (!m_canDraw)
        return;

    m_drawing.clear();
    update();
}