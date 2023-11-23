Integrantes do grupo:
-José Pedro Zago Fabris - 2019.1904.023-4
-Gabriel Santos Costa - 2019.1904.004-1
-Maria Luiza Beal de Oliveira - 2015.1904.045-8
-Pedro Henrique Ferrari Mascarenhas - 2023.1904.080-0


Descrição do trabalho: o trabalho consiste em um programa desenvolvido em c++ no Visual Studio Code 2022 que,em uma cena,
renderiza 3 objetos usando shaders :um losango,um cubo e uma piramide.Os objetos tambem giram automaticamente em torno do eixo y, ou 
em torno do eixo x, y e z manualmente com o uso do mouse(clicando no checkbox de animação),assim como optar por não renderiza-los clicando na checkbox do objeto correspondente.
Alem disso,adicionado do trabalho 1, foi implementado uma camera que pode swer contralada com o teclado:WASD para move-la, Q e E para mover o angulo e ao segurar o botao Alt é possivel move-la livremente com o mouse.
Luzes foram implemntadas no trabalho com a luz ambiente,difusa e especular(e tecnicamente a luz Phong tambem foi implementada ja que a mesma consiste na fusão das tres outras luzes.)
É necessario mexer nos sliders presente na interface grafica para mover e mudar a intensidade das luzes sendo o ultimo slider de cada luz sendo responsavel pela sua intensidade. 
Assim como a parte 1, o trabalho pode ser executado no visual studio code,rodando o arquivo solução do trabalho(\animacao-3d\apps\template\build\vs2022\myapp.sln), ou clicando
no executavel gerado após executa-lo no vscode.

A parte 1 do trabalho foi usada como base pare a implementação deste,então toda descrição envolvendo o copyright do trabalho anterior se aplica neste tambem.   

Voltando a descrição geral do código e uso dos shaders:

Os shaders foram implementados no documento "Fragments.cpp"
Fragment shader(fs):
Neste fragment shader, são realizados cálculos de iluminação, incluindo componente ambiente, difusa e especular, utilizando o modelo de reflexão de Phong. A atenuação é aplicada com base na distância da fonte de luz até o fragmento.
Vertex Shader(vs):
Neste vertex shader, a função TR é definida para construir uma matriz de transformação com base em rotação e translação. Os vértices são transformados pela matriz rotateTranslate e, em seguida, aplicadas as matrizes de projeção e visualização. As cores e as normais dos vértices também são passadas para o fragment shader, e a posição do fragmento é calculada após a transformação.

Ambos os shaders fazem parte do pipeline gráfico do OpenGL e são usados para processar os vértices e fragmentos de uma cena tridimensional, aplicando efeitos de iluminação e transformações geométricas.

