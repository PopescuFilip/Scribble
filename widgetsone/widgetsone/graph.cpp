#include "graph.h"

Graph::Graph(int radius):
    m_radius(radius),
    m_adjacencyMatrix(nullptr),
    matrixSize(0),
    m_oriented(false)
{}

Graph::Graph(const Graph& g)
{
    m_nodes = g.m_nodes;
    m_arches = g.m_arches;
    m_radius = g.m_radius;
    m_oriented = g.m_oriented;
    deallocateMatrix();
    allocateMatrix(g.matrixSize);
    for(int i = 0; i < matrixSize; i++)
        for(int j = 0 ; j< matrixSize; j++)
            m_adjacencyMatrix[i][j] = g.m_adjacencyMatrix[i][j];
}

Graph::~Graph()
{
    if (m_adjacencyMatrix)
        deallocateMatrix();
}

std::vector<Node> Graph::getNodes()const
{
    return m_nodes;
}

std::vector<Arch> Graph::getArches()const
{
    return m_arches;
}

int Graph::getRadius() const
{
    return m_radius;
}

int Graph::getMatrixSize() const
{
    return matrixSize;
}

Node* Graph::getAdressOfNode(int value)
{
    if(value >= m_nodes.size())
        return nullptr;
    return &m_nodes[value];
}

void Graph::setNode(int value, QPoint coordinate)
{
    if(value >= m_nodes.size())
        return;
    m_nodes[value].setCoordinate(coordinate);
}

void Graph::addNode(Node n)
{
    n.setRadius(m_radius);
    m_nodes.push_back(n);
    updateMatrixAfterAddNode();
}

void Graph::addNode(QPoint p)
{
    Node n(m_radius);
    n.setCoordinate(p);
    n.setValue(m_nodes.size());
    m_nodes.push_back(n);
    updateMatrixAfterAddNode();
}

void Graph::addArch(Arch a)
{
    m_arches.push_back(a);
    updateMatrixAfterAddArch();
}

void Graph::showNodes() const
{
    for (const Node &n : m_nodes)
        std::cout<< "(" << n.getValue() << "("  << n.getX() << "," << n.getY() << "))" << std::endl;
    std::cout << std::endl;
}

void Graph::showArches() const
{
    for (const Arch &a : m_arches)
        std::cout<< "(" << a.getFirstNode()->getValue() << ","  << a.getSecondNode()->getValue() << ")" << std::endl;
    std::cout << std::endl;
}

void Graph::toggleOriented()
{
    m_oriented = !m_oriented;
}

bool Graph::isOriented()
{
    return m_oriented == true;
}

bool Graph::isInGraph(QPoint p) const
{
    for (const Node& n: m_nodes)
        if (n.isInNode(p))
            return true;
    return false;
}

bool Graph::isInGraph(Arch a) const
{
    for (const Arch& arch: m_arches)
        if (arch == a)
            return true;
    return false;
}

bool Graph::positionIsAvailable(QPoint p) const
{
    for (const Node& n: m_nodes)
        if (!n.positionIsAvailable(p))
            return false;
    return true;
}

QPolygon Graph::createArrowHead(QPoint start, QPoint stop, int arrowSize) const
{
    QPolygon arrowHead;
    QLine line(stop, start);
    double angle = std::atan2(-line.dy(), line.dx());
    QPoint arrowP1 = stop + QPoint(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
    QPoint arrowP2 = stop + QPoint(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);
    arrowHead.clear();
    arrowHead << stop << arrowP1 << arrowP2;
    return arrowHead;
}

void Graph::deallocateMatrix()
{
    for (int i = 0; i < matrixSize; i++)
        delete[] m_adjacencyMatrix[i];
    delete[] m_adjacencyMatrix;
    matrixSize = 0;
}

void Graph::allocateMatrix(int newSize)
{
    m_adjacencyMatrix = new int*[newSize];
    for (int i = 0; i < newSize; i++)
        m_adjacencyMatrix[i] = new int[newSize]();
    matrixSize = newSize;
}

void Graph::updateMatrixValues()
{
    for (const Arch& arch: m_arches)
        if (arch.getFirstNode()->getValue() < matrixSize and arch.getSecondNode()->getValue() < matrixSize)
        {
            int firstValue = arch.getFirstNode()->getValue();
            int secondValue = arch.getSecondNode()->getValue();
            m_adjacencyMatrix[firstValue][secondValue] = 1;
        }
            
}

void Graph::updateFile(QFile& file)
{
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Failed to open the file.";
        return;
    }
    QTextStream out(&file);
    out << matrixSize << Qt::endl;
    for(int i = 0; i < matrixSize; i++)
    {
        for(int j = 0 ; j< matrixSize; j++)
            out << m_adjacencyMatrix[i][j] << " ";
        out << Qt::endl;
    }
}

void Graph::updateMatrixAfterAddNode()
{
    deallocateMatrix();
    allocateMatrix(m_nodes.size());
    updateMatrixValues();
}

void Graph::updateMatrixAfterAddArch()
{
    Arch arch = m_arches.back();
    m_adjacencyMatrix[arch.getFirstNode()->getValue()][arch.getSecondNode()->getValue()] = 1;
}



