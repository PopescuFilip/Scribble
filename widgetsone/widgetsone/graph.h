#pragma once
#include "Arch.h"
#include <iostream>
#include <QFile>
#include <QTextStream>

class Graph
{
private:
    std::vector<Node> m_nodes;
    std::vector<Arch> m_arches;
    int m_radius;
    int** m_adjacencyMatrix;
    int matrixSize;
    bool m_oriented;

    void deallocateMatrix();
    void allocateMatrix(int newSize);
    void updateMatrixAfterAddNode();
    void updateMatrixAfterAddArch();

public:
    Graph(int radius = 10);
    Graph(const Graph& g);
    ~Graph();

    std::vector<Node> getNodes()const;
    std::vector<Arch> getArches()const;
    int getRadius()const;
    int getMatrixSize()const;
    Node* getAdressOfNode(int value);

    void setNode(int value, QPoint coordinate);

    void addNode(Node n);
    void addNode(QPoint p);
    void addArch(Arch a);

    void showNodes()const;
    void showArches()const;

    void updateMatrixValues();
    void updateFile(QFile& file);

    void toggleOriented();
    bool isOriented();
    bool isInGraph(QPoint p)const;
    bool isInGraph(Arch a)const;
    bool positionIsAvailable(QPoint p)const;
    QPolygon createArrowHead(QPoint start, QPoint stop, int arrowSize)const;

};

