# Algoritmos-e-Estruturas-de-Dados

## Tema 4 – Inscrição de Estudantes 
### (Parte 1)
O plano de estudos do MIEIC inclui unidades curriculares obrigatórias e unidades curriculares optativas (no
4ºano/2ºsemestre e 5ºano/1ºsemestre). As unidades curriculares optativas possuem um número fixo de vagas,
pelo que o estudante só fica inscrito se tiver vaga. No caso de não existir vaga numa UC optativa que interessa
ao estudante, deve ser possível identificar rapidamente outras UCs da mesma área científica existentes em
outros cursos da Universidade do Porto. Inclua esta informação nas UCs optativas.
Implemente um sistema para inscrição de estudantes nas unidades curriculares do MIEIC (seguindo o plano de
estudos deste curso).
A inscrição de um estudante num ano letivo está limitada a 75 créditos e não é possível a inscrição em uma UC
de um ano curricular superior ao de UCs às quais o estudante, não tendo ainda obtido aprovação, não está
inscrito. O sistema deve registar a data da inscrição.
Um estudante é identificado por um código, nome, email e estatuto (pode considerar informação adicional).
Todos os estudantes possuem um tutor, que é um docente do MIEIC. No instante em que o estudante efetua a
inscrição, é-lhe atribuído um tutor. A escolha do tutor é efetuada de modo a equilibrar o número de estudantes
por tutor.
O sistema deve permitir a consulta de inscrições quer por estudante, quer por unidade curricular.
### (Parte 2)
Complemente o sistema já implementado com as seguintes funcionalidades:

● O tutor realiza reuniões periódicas com os estudantes a seu cargo. O tutor guarda numa árvore binária
de pesquisa, estas reuniões, ordenadas por data. A informação a guardar sobre a reunião inclui
data,idenficação
do estudante, agenda e descrivo.
O tutor pode marcar reuniões com os seus
estudantes, cancelar reuniões e alterar o descrivo
da reunião. Deve ser possível também obter uma
listagem das reuniões já ocorridas ou a realizar em determinado período.

● A atribuição de turmas a estudantes é efetuada em dois passos. Num primeiro passo, o sistema coloca o
estudante numa turma do seu ano base (ano base é o ano curricular em que o estudante possui mais
UCs), ficando o estudante colocado na mesma turma em todas as UCs desse ano curricular. Num
segundo passo, o estudante escolhe manualmente turmas para as UCs que não são do seu ano base
(neste trabalho, não é necessário considerar este segundo passo). Considere que as turmas estão em
filas de prioridades (uma fila para cada ano curricular) ordenadas por número de vagas. O estudante é
alocado a uma turma, se essa turma possui vagas em todas as UCs do seu ano base. As turmas com
maior número de vagas devem ser preenchidas primeiro. Considere que no topo da fila de prioridade se
encontra a turma com o maior número de vagas da UC mais ocupada da turma. O sistema deve permir
alocar um estudante numa turma (a determinar pelo sistema), acrescentar turmas ou eliminar turmas.
Deve ser ainda permido
consultar as vagas nas UCs das 3 turmas no topo da fila de prioridade.

● Estudantes que terminaram ou interromperam o curso, são guardados numa tabela de dispersão. Deve
ser possível verificar o estado dos estudantes presentes na tabela de dispersão (concluído /
interrompido). Se um estudante que interrompeu o curso efetua nova inscrição, é rerado
da tabela de
dispersão e passa novamente para o sistema. As moradas e contactos dos estudantes em qualquer
estado devem ser atualizadas, se necessário, de forma a ter esta informação sempre válida.
