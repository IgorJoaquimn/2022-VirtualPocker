# 2022-VirtualPocker
# Trabalho Prático 1

```
DCC214 - Estrutura de Dados
Igor Joaquim da Silva Costa
```
## 1. Introdução

Oproblemapropostofoisimularumjogodepokervirtualentreosalunosdeumasala.
Paraumconjuntodejogadoresesuasrespectivascartasemumarodada,deveria-secomputar
quaisseriamospossíveisganhadoreseaquantiadedinheiroqueelesreceberiam,apartirdas
regrasdojogodePoker.Aofinaldetodasasrodadas,umplacarordenadopelaquantiade
dinheiro deveria ser montado.
Pararesolveroproblemacitado,foiseguidaumaabordagemvoltadaàprogramação
orientadaaobjetosnalinguagemc++,ondecadaobjetorepresentapartedamodelagemdo
mini-mundodeinteresse.Apartirdisso,asimulaçãodojogoacontecepelamútuainteração
entreobjetospormeiodemétodospróprios,ondecadaTADcontémasresponsabilidadesde
suas respectivas entidades, garantindo a consistência do sistema.
Diantedoexposto,adocumentaçãopresentepossuicomoobjetivodetalharcomoo
sistemafoiimplementado(Seção2),oquãoeficienteelepodeseremtermosteóricos(Seção
3) e aplicados (Seção 5), além de explicar como o programa lida com possíveis
inconsistênciasduranteaexecuçãodojogo(Seção4).Porfim,oprojetoésumarizadojunto
com os aprendizados gerados durante a produção do trabalho(Seção 6).

## 2. Método

Como abordado na seção 1, ocódigogeradousaextensivamenteosconceitos de
Programação Orientada à Objetos como uma maneira de organizar e implementar as
responsabilidades dosistema.Dessemodo, foramretiradastrêsentidadesfundamentaisdo
mini-mundopoker:carta,jogadore“rodada”,ondeaúltimamodelaosestadosdosjogadores
em uma rodada específica.


# 2.1 Fluxo principal

Otópicoatual temcomoobjetivo esclareceranível conceitualcomoasdiferentes
classes se relacionam, explicando o fluxo principaldo programa. As partesem negrito
representam os nomes das classes e métodos utilizados.
Oprimeiropassonaexecuçãodocódigosetratadaleituradaquantidadederodadas
presentesnojogoedaquantiadedinheiroinicialdosjogadores.Comessasinformaçõesem
mãosépossíveliniciaraprimeira **rodada** .Cada **rodada** écompostapor **jogadores** ,apostase
**cartas.** Caso algum jogador não possa contribuir com a aposta estipulada, a rodada é
invalidadae o“ **dinheiroresetado** ”,ouseja,aquelesjogadoresquejácontribuíramcomo
pote nessa jogada ganham seu dinheiro de volta. Nas rodadasválidas,o jogo **calcula a
rodada** edeterminaosganhadores,repartindoopoteentreeles.Parase **calculararodada** ,
bastaencontrarquais **jogadores** podemperformaras **jogadas** denívelmaisalto.Porfim,as
informações da **rodada** e o **estado final** do jogo sãoarmazenadas em um arquivo de saída.
Adiante, estão as implementações dessas classes.

# 2.2 Estrutura de dados: Lista_ordenada

Como diversas partes do programa necessitam de algum tipo de ordenação, a
necessidadedearmazenardadoscomalgumaordemembutidatornouválidaaexistênciade
umaclassecomtalpropriedade.Nessesentido,oTADlistaordenadaéumaclassetemplate,
ou seja, umaclasse capaz detrabalharcomqualquertipode variávelquecumpracertas
especificações mínimas de funcionalidade. No caso presente, qualquer elemento com a
operação“menorque”podeserusadaparaaconstruçãodeumalista_ordenada,queordena
elementosduranteainserção.Asúnicasatribuiçõesdeumalistaordenadasãoabuscaea
inserçãodeelementos.Abuscafoiimplementadausandoumalgoritmodebuscasequenciale
ainserçãoprocuraoprimeiroelementomenordoqueaquelequeestáparaserinserido,se
esse elemento não existir, o novo elemento é inserido ao final da lista.

## 2.2.1 Node_t

Para a implementação da lista encadeada ordenada, foi criada uma outraclasse
templatechamadanode_t,quefuncionacomoacéluladeumalistaduplamenteencadeada.Os
únicos atributos dessa classe são ponteiros, um paraapróxima célula,umparaa célula
anterior e outro para o conteúdo armazenado.


# 2.3 Classes

## 2.3.1 Carta

TADresponsávelporrepresentarumacartadepoker,ondecadacartaécompostapor
uma letra que representa um naipe e um número entre 1 e 13.

Implementação:
-Atributos: a classe carta possui 2 atributos privados, naipe e número.
-Operadores:
Igualdade: Duas cartas são iguais se tiverem o mesmo NÚMERO.
Menor que: Uma carta é menor do que a outra se o NÚMERO da primeira for menor.

## 2.3.2 Jogador

TADresponsávelporgerirasresponsabilidadesdeumjogadornapartida.Ojogadoré
entendidocomoaentidadequepossuiumaquantiainteiradedinheiro,umnomeeumamão,
ouseja,umconjuntodecincocartas.Noquesitoresponsabilidade,ojogadordevesercapaz
deinterpretarqualjogadacorrespondeasuamãoatual,aumentarediminuiroseudinheiroe,
aofinaldeumajogada,devolversuascartasaobaralho,alémdeverificarseasapostasfeitas
por ele seguem as regras do jogo.
Nesse sentido,a classejogadorpossuiatributosemétodosparamodelar cadaum
dessescomportamentos,como,porexemplo,afunçãoset_aposta(),queverificaseaaposta
apresentada pelo jogador é múltipla de 50 e menor do que o dinheiro que ele possui
atualmente, como é definido nas especificações do jogo.
Noquetangeadinâmicadojogodepoker,umdetalheimportantedaclassejogadoré
seuatributo“mao”,queédotipolista_ordenada<carta>.Armazenandoascartasdemaneira
ordenada,averificaçãodequaisjogadaspossíveisumconjuntodecartaspodeperformarse
tornamaisfácil,jáque muitasjogadasdependemdeexistênciasdenúmerosconsecutivos
entreascartasoudeterminaçãodacartademaiornúmero.Alémdoatributomão,oatributo
valor_jogadatambémécrucialparaofluxodejogo.Nelesãoarmazenadosovalordamaior
jogadapossível dese realizarcomamãoatualdojogadoreocritériodedesempatepara
aquela jogada,facilitandoa interaçãoentreváriosjogadores,jáqueesseatributopodeser
usado para determinar os ganhadores de uma rodada.


Porfim,aclasseusadesobrecargadeoperadoresparafacilitarabuscadeumjogador
emespecíficoeaordenaçãodosmesmos.Umjogadoréigualaooutroseosnomesforem
iguaiseumjogadorémenorqueoutroseovalor_jogadadoprimeiroformenordoqueodo
segundo. Caso ambos jogadores tenham o mesmo valor de jogada (variável x do par
valor_jogada),ocritériodedesempate(variávely)setornadecisivo.Seaindaassimnãofor
possíveldecidirqualdosdoiséomenor,aoperaçãoédecididapelojogadorquepossuimaior
o nome em ordem lexicográfica.

## 2.3.3 Rodada

Afimdegerenciaroestadodediversosjogadoresduranteapartida,foicriadooTAD
rodada,aclassequedecidequaisjogadoresganhamdeterminadajogadaeatribuiovalordo
pote a eles.
O principalmétodo da listade jogadoreséo“calcula_rodada()”, onde, dadauma
rodada em específico, é determinada qual a jogada com o maior valor possível de ser
executada,além dedeterminarquaisjogadorespodemperformá-la.Ométodoalcançaesse
objetivousandoduasestruturasauxiliares,aprimeirasetratandodeumarray de 10
funçõesquerepresentaas 10 jogadaspossíveis,ordenadasdamenorparaamaior,easegunda
dométodocalcula_ganhadores(),onde,dadaumadas 10 jogadas,sãoarmazenadostodosos
jogadoresque podemrealizar aquelajogadaemumarrayauxiliar.Dessaforma,ométodo
calcula_rodada()percorreas 10 possíveisjogadasarmazenadasnoarraydeformadecrescente
atéencontraraprimeiraquealgumjogadorpossafazer,apósessepasso,afunçãopercorreo
arraycompostoapenaspelospossíveisganhadoresparadeterminarquaisdefatovãoganhara
rodada, combase no parâmetrovalor_jogada da classe jogador. Sabendo osíndicesdos
jogadoresquepassamdocritériodedesempate,afunçãodivideopoteentreelesearmazena
essas informações no arquivo de saída.
Alémdisso,aclassetambémgarante aintegridade dojogoaoevaluarsetodosos
jogadorespodemcontribuirparaopingopelafunçãoset_pingo(),reiniciandoarodadaem
casodeerroouaofinaldetodasasjogadascomafunçãoreseta_jogadas()edevolvendoo
dinheiro ao jogadores, caso necessário, na função reseta_dinheiro().


# 2.4 Jogadas

As funções jogadas são representações das 10 possíveis configurações de mãos
presentes no jogo de poker. Cada jogada possuium valorúnico e precisa cumprirseus
critériosprópriosparaacontecer,sãoelasquedecidemquaissãoospossíveisganhadoresde
uma rodada. Além disso, cada jogada segue seu próprio critério de desempate, se existir.
Ditoisso,todasasfunçõesjogadasdoprogramasãoreflexosdasjogadasreais,salvo
algumasmudançasparaseadequaraespecificaçãodotrabalhoeparalidarcompartesnão
especificadas,comonocasodoscritériosdedesempatedecadafunção.Aideiaprincipaldas
funções jogada é determinar se a mão de um dado jogadorconfiguraaquela jogadaem
específico,sesim, oatributo valor_jogadadojogadoréatualizadoparaovalordajogada
analisadoeafunçãoretornatrue,senão,elaretornazero.Dessaforma,setornaconvenientea
comparação de jogadas entrediversosjogadores,visto que jogadorescommaior atributo
valor_jogada possuem mãos mais fortes do que as dos seus oponentes.
Além disso, a segunda variável do atributo valor_jogadaarmazena o critério de
desempatedojogador,sendopossíveldesempatarojogocasonecessário.Asfunçõesjogadas
fazemessecálculodedesempateusandoasregrasdojogodepoker,como,porexemplo,a
funçãoflush,quearmazenaovalordacartamaisaltadojogadorcomocritériodedesempate,
fazendo comque doisjogadorescapazesde executarumflush tenhamvaloresde jogada
diferente, baseadonesse segundo parâmetro. Para jogadas com maisde umganhador,o
segundoparâmetroé constanteno valor0. Ademais,jogadascommaisdeumcritériode
desempatetambémsãocalculadasdamesmaforma,como,porexemplo,ajogadaThreeofa
kind,queemcasodeempateéconsideradaamaiorcartadatriplae,emcasodeumsegundo
empate,amaiorcartaentreosjogadores,seucritériodedesempateédaformula 100 *(maior
númerodatripla)+(cartademaiornúmero),garantindoqueocritériodedesempatecontinue
válido.
Porfim,existemasjogadascomcritériosdedesempatenãoespecificadosparatodo
tipodesituação,comoajogadaONEPAIR,ondeocritériodedesempateprimárioéovalor
da maior carta no par e o critériosecundário sendo a maior carta na mão do jogador.
Definiçõesdessa formacausam problemasemalgunscenários,comonoscasosondedois
jogadorespossuemomesmopar e amesmacartamaisalta,ficandoincertocomodecidir
quem são osganhadores. Em todos oscasos possíveis dessa incertezaacontecer,ambos
jogadoressãoconsideradosganhadores,mesmoemjogadasondeapenasumjogadorpoderia
ganhar.


## 3. Análise de complexidade

# 3.1 Espaço

Comoestamoslimitadosaumbaralhode 52 cartas,onúmeromáximodejogadoresé
10, já que 11*5 = 55, que ultrapassa o número de cartas do baralho. Ainda assim,
considerandoonúmerodejogadorescomoavariávelNeoespaçoparaarmazenarumacarta
sendo1,aquantidademáximadeespaçoqueoprogramaocupaéΘ( 2 * 5 𝑁),jáque,para
cada jogador, são armazenadas 5 cartas, além de seremcriadas duaslistasdejogadores
adicionais,umaparaarmazenarosganhadoreseoutraparaarmazenaroplacar,valedizerque
ambasnãoexistemaomesmotempo.Ditoisso,oprogramaéO(N)noespaço,ouseja,ele
independe da quantidade de rodadas efetuadas.

# 3.2 Tempo

Paraanálisedetempo,considereNcomoonúmerodejogadoreseRcomoototalde
rodadas.

## 3.2 Inserção/Busca

Considerando a comparação como operação mais significativa, como tanto os
jogadoresquantoascartassãoordenadosnomomentodainserção,omelhorcasoéO(1),que
equivaleainseriromenorelementonalista.Opiorcaso,inseriromaiorelemento,éO(N),
vistoquesãonecessáriasaomenosNcomparaçõesparainserirumelementoaofinaldalista.
Demaneiraanáloga,abuscatambéméO(1)nomelhorcaso,procuraromenorelemento,e
O(N)nopiorcaso,procuraroúltimoelemento,jáqueoalgoritmodebuscautilizadosimula
umabuscasequencial.Dessaforma,tantoaInserçãoquantoaBuscasãoO(N)nonúmerode
elementosnopiorcaso.Nocontextodeumarodada,ondecadajogadorsempreébuscadoou

inserido,acomplexidadesetorna𝑂(𝑁^2 ),vistoque,paracadaumdosNjogadorespresentes,
acontece uma operação que é O(N) no pior caso. No contexto de múltiplas rodadas, a

complexidade cresce para𝑂(𝑅*𝑁^2 ).

## 3.3 Executar jogadas

Considerando a comparação como a operação maissignificativa, no contexto de
determinarajogadadeapenasumjogador,sãofeitasO(10*5)comparaçõesnopiorcaso,já


que,paracadajogada,énecessárioanalisaras 5 cartasnamãodojogador.NocontextodeN
jogadores,somenteexecutarasjogadassetornaO(10*5*N). Entretanto,comoasjogadas
precisamserdesempatadaseopoterepartido,sãofeitasmaisO(N+N)operaçõesnocaso
que todososjogadoresganhamna mesmarodada.Dessaforma,acomplexidadesetorna
O(10*5*(3N)).NocontextodemúltiplasrodadasacomplexidadesetornaO(10*5*(3N)*R)
= O(R*N), ou seja cresce linearmente no número de rodadas e no número de jogadores.

## 3.4 Testes de sanidade

Considerandoa comparaçãoeo módulocomoasoperaçõesmaissignificativas,no
contextodeumarodadacomNjogadores,acomplexidadedeexecutarumtestedesanidadeé
O(N),jáque,paracadajogador,aoperaçãocorrespondenteaessetestedesanidadeéfeita.
Comosãofeitos 3 testesdesanidadeemumarodada,acomplexidadesetornaO(3*N).No
contexto demúltiplasrodadas, acomplexidade cresceparaO(R*N*3)=O(R*N),ouseja,
cresce linearmente com o número de rodadas e com o número de jogadores.

## 3.5 Complexidade final

Considerandoqueacadarodada,sãofeitasinserções,buscas,execuçõesderodadase
testes de sanidade, a complexidade total do programa fica

𝑂(𝑅*(𝑁^2 +𝑁+𝑁))=𝑂(𝑅*𝑁^2 ),ouseja,linearnonúmeroderodadasequadráticono
número de jogadores.

## 4. Estratégias de Robustez

# 4.1 Testes de sanidade

Como especificado na descrição do jogo, toda aposta deveser múltipla de 50 e
nenhumjogadorpodeapostarmaisdoque elepossui,dessaforma,afunçãoset_aposta()
retorna falso para todo caso que não segue essasregras.Assim,todarodadaque possui
alguma inconsistência não é considerada no placar final do jogo.


## 5. Análise Experimental

Aanáliseexperimentalaseguirtemcomoobjetivomediroquãoeficienteéosistema
implementadousandoduasmétricas,odesempenhocomputacional-quãorápidooprograma
é executado com entradas grandes - e análises de acesso em memória.

# 5.1 Desempenho computacional

## 5.1.1 Perfil de execução

Para testarodesempenhocomputacional,primeiramente,oprogramafoicompilado
em estadode "profiling",a fimde analisarquais funções consomemrelativamentemais
tempoduranteaexecuçãodoprograma.Diantedisso,foramfeitastrêsexecuções,cadauma
compostapor100.000rodadasaleatórias,geradasporumcódigopythonexternofeitopelo
aluno.Comoprofiledasexecuçõespronto,cadaumafoidadocomoentradanoprograma
“gprof”,umaferramentaque auxilianaanálise dodesempenhocomputacional.Dito isso,
segue a análise das chamadas de funções.

Teste 1:

```
Tempo de
execução
(%)
```
```
Calls
Função
17.07 2998855 lista_ordenada<carta>::insert(carta*)
9.76 int __gnu_cxx::__stoa<long, int, char, int>(long (*)(char const*, char**, int))
9.76 std::__cxx11::stoi(std::__cxx11::basic_string<char)
7.32 le_partida(std::basic_ifstream<char, std::char_traits<char> >&, rodada&, int)
7.32 carta::carta(std::string)
7.32 carta::operator<(carta const&) const
7.32 _init
6.10 2998855 jogador::insert(std::string)
```
```
4.
```
```
__gnu_cxx::__stoa<long, int, char, int>(long (*)(char const*, char**, int), char
const*, char const*, unsigned long*, int)::_Save_errno::_Save_errno()
3.66 2197492 jogador::limpa_mao()
```
```
2.44 3176935
```
```
__gnu_cxx::__enable_if<std::__is_char<char>::__value, bool>::__type
std::operator==<char>(std::__cxx11::basic_string<char,
std::char_traits<char>, std::allocator<char> > const&,
2.44 3176935 operator==(jogador const&, jogador const&)
2.44 998220 jogador::reseta_dinheiro()
```

```
2.44 602760 jogador::set_aposta(int)
2.44 599781 jogador::jogador(std::string)
2.44 rodada::find(std::string)
2.44 __gnu_cxx::__stoa<long, int, char, int>(long (*)(char const*, char**, int)
1.22 2998855 node_t<carta>::node_t(carta*&)
1.22 1532 int& std::forward<int&>(std::remove_reference<int&>::type&)
```
Para evitar redundância, os outros perfis de execução apresentam o mesmo
comportamento dotesteapresentadoacima.Noquetangeaanálisedosexperimentos,fica
evidenteque afunçãoque maisdemandatempo,emporcentagem,éafunçãoparainserir
ordenadamenteascartasnamãodeumjogador.Nocasodemonstradosãofeitas 5 inserções
por jogador por jogada, um número que pode chegar a 5000000 se todos osjogadores
participaremdetodasasrodadas.Alémdisso,afunçãoapresentacomplexidadequadrática,
contribuindo para uma grande parcela de tempo.
As funçõesque ocupamasegundaeterceiraposiçãosãofunçõesquetransformam
strings em inteiros, outraoperação que acontece durante a leituradosdados daentrada,
especificamenteparalerovalordaapostaeparaleronúmerodascartas.Implementaruma
leitura diretamente com números inteiros resolveria esse problema.
Oquartolugarcorrespondeafunçãodeleituradoarquivo,oquefazsentido,jáquea
leituradealgoqueestáemmemóriasecundárianãoétãoeficazquantoaleituraemmemória
primária.Dessepontoemdiante,asfunçõesquegastammaistemposãoaquelasligadasa
simulaçãodojogodepokerequeocorremváriasvezesnamesmarodada.Éválidocomentar
sobreaperformancedafunçãodecomparaçãoentrecartas,jáqueelaéexecutadatodavez
que umacartaé inserida,ocasionandoemum grandegastodetempo,mesmosendouma
funçãorelativamentebaratadeexecutar.Porfim,afunçãocommaiornúmerodechamadas
correspondeacomparaçãoentrejogadores,queacontece 2 vezesacadaoperaçãodeprocura
na lista ordenada.
Nessesentido,conclui-sequeaindaexistemmargensparaamelhoranodesempenho
doprograma,aníveldechamadasdefunções,vistoquemuitasdelaspoderiamserfeitasde
outras formas, a fim de melhor utilizar tempo de execução do programa.


## 5.1.2 Desempenho em termos da entrada

Alémdotempogasto pelaschamadasde funções, deve-semedirarelaçãoentreo
aumentodovolumedaentradadoprogramacomoseutempodeexecução.Pararealizartal
objetivo,foiutilizadaaferramentaMemlogdoprofessorWagnerMeiraeferramentasparaa
geração de gráficos. A seguir, o gráfico com os resultados.

Comovistoacima,otempodeexecuçãocrescelinearmentecomoaumentodarodada,
assim como foi discutido na seção de análise de complexidade.

# 5.2 Análise de localidade de referência e acesso de memória

Comoexplicadoemaula,programaseficientesemusodememóriasãoaquelesque
tendemaacessarregiõesdememóriacontíguas,jáqueessapráticaéotimizadapelossistemas
operacionais onde o programa é executado. Tal propriedade échamadade localidadede
referência e é uma ótima métrica de como o programa acessa a memória por ele utilizada.
Nessesentido,munidodasferramentasAnalisamemeMemlog,disponibilizadaspelo
professorWagnerMeira,épossívelgerargráficosquedemonstramoacessodememóriado
programaemsuasdiversas fases,e,assim, analisar seoacessodememóriadoprograma
segueasboaspráticasdesejadas.Ditoisso,segueaanálisedeacessodememóriaelocalidade
dereferência,ondeoid 0 representaosnodesdalistaordenada,oid 1 osjogadoreseoid 2 as
cartas.



Comovistoacima,oprogramaacessadiversasvezesposiçõesdememóriaadjacentes,
issoaconteceporquesemprequearodadaéresetada,amemóriautilizadapelarodadaanterior
éliberadaeéreutilizadapelapróxima.Dessaforma,oprogramatrabalhaemsintoniacomos
conceitos essenciaisdosistemaoperacional, sempredemandando eacessandoposiçõesde
memória já utilizadas antes, dando margem para que esse processo seja otimizado pelo SO.
Entretanto,existemoutrasformasdemedirdiretamentealocalidadedereferênciado
sistema, analisando a distânciade pilha nasdiversasfases doprograma. Nessesentido,
seguemosgráficosdedistânciadepilhaemfases,ondeafase 0 englobaaleituradoarquivo,
afase1,ostestesdesanidade,afase2,ocálculodosganhadoreseafase3,orecomeçoda
jogada.







Dessaforma,conclui-sequeosistemamanteveumabaixadistânciadepilhadurante
todaaexecução,favorecendoahipótesedoacessoemposiçõescontíguasdememóriaesendo
uma forte prova de que o programa preza por uma boa localidade de referência.

## 6. Conclusões

Comointuitodesimularumjogodepokerentrealunosdeumasala,foiprojetado,
implementado, pensado e testado um sistema de computação que, dado umconjunto de
rodadas,jogadores,cartaseapostas,computaquemsãoosganhadoresdecadarodadaequem
terminou com mais dinheiro.
Duranteoprojetodosistemaforamlevadasemconsideraçãonãosóaspectoslúdicos
dojogodepoker,mastambémcomoalinguagemdeprogramaçãoescolhidapoderiaseruma
ferramentaútilparachegarnoobjetivoesperado.Todaaquestãodemapearummini-mundo
deinteresseemummodelocomputacionalrobustosemostroubastanteprodutiva,levandoo
alunoapensaremformascriativasde seresolveroproblema,como,porexemplo,armazenar
o critério de desempate juntoao jogador, possibilitando os desempatesde maneiramais
simples.Porfim,otempoextrausadoparaprojetarosistematrouxeváriasrecompensasno
sentido da implementação, sendo um aspecto a ser levado para trabalhos futuros.
Além disso,os testese aanálise decomplexidade semostraram muitoúteispara
entendercomoasentradasinfluenciamaexecuçãodoprogramaecomoalgunsdetalhesde
implementação podem ser significativos em termos de desempenho computacional e
localidade de referência.
Nessesentido,todoofluxodetrabalhofoiessencialparaaconsolidaçãodeconteúdos
aprendidos emsala, além de apresentar,de formaprática,comosoftwaresmaiores, mais
consistentes e robustos são projetados e implementados.

## 7. Bibliografia:

Ziviani,N.(2006).ProjetosdeAlgoritmoscomImplementaçõesemJavaeC++:Capítulo3:
Estruturas de Dados Básicas. Editora Cengage.

IBM, Documentação da Linguagem C. Class Templates
https://www.ibm.com/docs/en/zos/2.2.0?topic=only-class-templates-c


## 8. Instruções para compilação e execução:

## 8.1 Compilação

Existempartesdoprogramaquesãocompatíveisapenasàsversõesmaisrecentesda
linguagem c++, dito isso, deve-se seguir as seguintes configurações para a compilação:

```
Linguagem: C++
Compilador: Gnu g++
Flags de compilação:-std=c++11 -g
Versão da linguagem: standard C++1 1
Sistema operacional (preferência): distribuições baseadas no kernel Linux 5.15.
```
Ocomandoparacompilaroprogramaautomaticamenteestápresentenoarquivo **“Makefile”**
esuaexecuçãoéchamadapelocomando **“makeall”** .Aindaassim,seguemasinstruçõespara
compilar manualmente:

Parageraroexecutáveldoprograma,énecessário,primeiro,geraroobjetoparacadaarquivo
presentenapasta“/src”.Talobjetivopodeseralcançadoseguindoosseguintescomandosem
ordem:

```
g++ -std=c++11 -g -Wall -c src/jogadas.cpp -o obj/jogadas.o -I./include/
g++ -std=c++11 -g -Wall -c src/memlog.cpp -o obj/memlog.o -I./include/
g++ -std=c++11 -g -Wall -c src/jogador.cpp -o obj/jogador.o -I./include/
g++ -std=c++11 -g -Wall -c src/rodada.cpp -o obj/rodada.o -I./include/
g++ -std=c++11 -g -Wall -c src/main.cpp -o obj/main.o -I./include/
g++ -std=c++11 -g -Wall -c src/carta.cpp -o obj/carta.o -I./include/
```
Apósessepasso,deve-sejuntartodososobjetosemumúnicoarquivoexecutável,seguindoo
comando:
g++ -std=c++11 -g -Wall -o ./bin/tp1.out ./obj/jogadas.o ./obj/memlog.o ./obj/jogador.o ./obj/rodada.o
./obj/main.o ./obj/carta.o

Deste modo, o executável “/bin/tp1.out” estará compilado e pronto para ser utilizado.


### 8.2 Execução

Demaneiraanáloga, existeum comandono“Makefile”queexecutaocompilável,
chamado **“makeexec”** ,que secertificaqueosobjetosforamgeradosequeocompilável
existe. Ainda assim, seguem as instruções para a execução manual:

1. Certifique-se que o compilável foigeradode maneiracorreta,sealgum problema
    ocorrer, execute o comando “make all” presente no “Makefile”.
2. Dadoque ocompilável foigeradode maneiracorreta,certifique-sequeexisteum
    arquivo“entrada.txt”naraizdoprojeto,éessearquivoque“alimenta”oprograma.Se
    ele não existir, crie-o.
3. Uma vez que os passos anteriores foram cumpridos, executeo programa com o
    comando: ./bin/tp1.out
4. A saída estará guardada no arquivo “saida.txt”, na raiz do projeto.


