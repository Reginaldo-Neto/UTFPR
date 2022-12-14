class Graph:
    def __init__(self, Nvertices):
        self.Nvertices = Nvertices
        self.matriz = []

        for x in range(Nvertices):
            self.matriz.append( [0] * Nvertices )
    def addEdge(self, Vsai, Ventra, peso=1):
        for x in range (self.Nvertices):
            if(Vsai == x):
                for y in range (self.Nvertices):
                    if(Ventra == y):
                        self.matriz[x][y]=1
    def getInDegree(self, vertice):
        entrada=0
        for x in range (self.Nvertices):
            if(self.matriz[x][vertice]==1):
                entrada=entrada+1
        return entrada
    def getOutDegree(self, vertice):
        saida=0
        for y in range (self.Nvertices):
            if(self.matriz[vertice][y]==1):
                saida=saida+1
        return saida
    def getDegree(self, vertice):
        geral=0
        geral = self.getInDegree(vertice)
        geral = geral + self.getOutDegree(vertice)
        return geral        
