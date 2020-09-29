programa
{
	inclua biblioteca Arquivos --> arq
	inclua biblioteca Texto --> txt
	inclua biblioteca Tipos --> tp
	
	const inteiro MAX_US = 20
	const inteiro COL_US = 6
	const inteiro MAX_ESTAB = 4
	const inteiro COL_ESTAB = 2
	inteiro iglobal = 0
	inteiro jglobal = 0
	cadeia input = ""//input generico
	
	funcao carregarDados(cadeia m[][], cadeia m2[][]){
		se(nao(arq.arquivo_existe("usuarios.txt"))){
			inteiro criar = arq.abrir_arquivo("usuarios.txt", arq.MODO_ESCRITA)
			arq.fechar_arquivo(criar)
		}
		senao{
			inteiro endereco = arq.abrir_arquivo("usuarios.txt", arq.MODO_LEITURA)
			para(inteiro i = 0;i < MAX_US;i++){
				iglobal++
				para(inteiro j = 0;j < COL_US;j++){
					se(arq.fim_arquivo(endereco)){
						arq.fechar_arquivo(endereco)
						i = MAX_US
						j = COL_US
						iglobal--
					}
					senao{
						m[i][j] = arq.ler_linha(endereco)
					}
				}
			}
		}
		se(nao(arq.arquivo_existe("estabs.txt"))){
			inteiro criar = arq.abrir_arquivo("estabs.txt", arq.MODO_ESCRITA)
			arq.fechar_arquivo(criar)
		}
		senao{
			inteiro endereco = arq.abrir_arquivo("estabs.txt", arq.MODO_LEITURA)
			para(inteiro i = 0;i < MAX_ESTAB;i++){
				jglobal++
				para(inteiro j = 0;j < COL_ESTAB;j++){
					se(arq.fim_arquivo(endereco)){
						escreva("entrou\n")
						arq.fechar_arquivo(endereco)
						i = MAX_ESTAB
						j = COL_ESTAB
						jglobal--
					}
					senao{
						m2[i][j] = arq.ler_linha(endereco)
					}
				}
			}
		}
	}

	funcao cadeia enter(cadeia in){
		in = txt.caixa_baixa(in)
		se(in == ""){
			in = "s"
		}
		retorne in
	}
	
	funcao cadastrarUsuario(cadeia m[][], inteiro &ig){
		faca{
			limpa()
			m[ig][0] = tp.inteiro_para_cadeia(ig, 10)
			escreva("Digite o nome do usuário: ")
			leia(m[ig][1])
			escreva("Insira o CPF do usuário: ")
			leia(m[ig][2])
			ig++
			escreva("Deseja cadastrar outro usuário? (S/n)\n")
			leia(input)
			input = enter(input)
		}
		enquanto(input == "s")
		
	}

	funcao menu(){
		escreva("\n\t\t PLATAFORMA CORONAVIRUS\n")
    		escreva("\t 1 - Cadastrar usuario\n")
    		escreva("\t 2 - Listagem de usuarios\n")
    		escreva("\t 3 - Listagem de estabelecimento\n")
    		escreva("\t 4 - Realizar Check-In\n")
    		escreva("\t 5 - Checar risco de contaminação\n")
    		escreva("\t 0 - Fechar programa\n")
	}

	funcao listagemUsuarios(cadeia m[][]){
		limpa()
		cadeia vmatriz = ""
		para(inteiro i = 0;i < iglobal;i++){
			para(inteiro j = 0;j < 1;j++){
				cadeia print = "\n"
				se(m[i][j+3] == ""){
					escreva("\n | ", m[i][j], " | ", m[i][j+1], " | ", m[i][j+2], " | (Este usuário não realizou check-in)")
				}
				senao{
					para(inteiro k = 0;k < COL_US;k++){
						vmatriz = m[i][j+k]
						print += (" | " + vmatriz)
					}
					escreva(print)
				}
			}
		}
	}
	
	funcao listagemEstab(cadeia m[][]){
		escreva("\nID\tESTABELECIMENTOS\n")
		cadeia vmatriz = ""
		para(inteiro i = 0;i < jglobal;i++){
			para(inteiro j = 0;j < 1;j++){
				cadeia print = "\n"
				para(inteiro k = 0;k < COL_ESTAB;k++){
					vmatriz = m[i][j+k]
					print += (" | " + vmatriz + " | ")
				}
				escreva(print)
			}
		}
	}

	funcao checkIn(cadeia m[][]){
		inteiro id = 0
		cadeia cont = ""
		faca{
			limpa()
			escreva("Paciente já é usuário? (S/n)\n")
			leia(input)
			input = enter(input)
			se(input == "n"){
				cadastrarUsuario(m, &iglobal)
			}
			listagemUsuarios(m)
			escreva("\n\nInsira o ID do usuário que fará o Check-In: ")
			leia(id)
			se(id > iglobal ou id < 0){
				escreva("ID inválido\n")
			}
			senao{
				escreva("Digite a data da realização do teste(formato: dia/mes, ex:01/07): ")
				leia(m[id][3])
				se(tp.cadeia_e_inteiro(txt.extrair_subtexto(m[id][3], 0, 2), 10)){
					inteiro checkdia = tp.cadeia_para_inteiro(txt.extrair_subtexto(m[id][3], 0, 2), 10)
					se(checkdia > 31 ou checkdia < 1){
						escreva("Dia inválido\n")
					}
					senao se(tp.cadeia_e_inteiro(txt.extrair_subtexto(m[id][3], 3, 5), 10)){
						inteiro checkmes = tp.cadeia_para_inteiro(txt.extrair_subtexto(m[id][3], 3, 5), 10)
						se(checkmes > 12 ou checkmes < 1){
							escreva("Mês inválido\n")
						}
						senao{
							escreva("Insira o resultado do teste de COVID-19 do paciente(Positivo/Negativo): ")
							leia(m[id][4])
							m[id][4] = txt.caixa_alta(m[id][4])
							se(m[id][4] != "POSITIVO" e m[id][4] != "NEGATIVO"){
								escreva("Resultado inválido\n")
							}
							senao{
								escreva("Insira o estabelecimento em que o teste foi realizado: ")
								leia(m[id][5])
								escreva("Check-In registrado!\n\n")
								escreva("Deseja cadastrar outro Check-In? (S/n)\n")
								leia(cont)
								cont = enter(cont)
							}
						}
					}
				}
			}
		}
		enquanto(cont == "s")
	}

	funcao checarRisco(cadeia m[][]){
		limpa()
		inteiro riscos = 0
		para(inteiro id = 0;id < iglobal;id++){
			para(inteiro i = 0;i < iglobal;i++){
				se((m[id][3] == m[i][3]) e (m[id][4] == "NEGATIVO") e (m[i][4] == "POSITIVO") e (m[id][5] == m[i][5])){
					escreva("\nRISCO DE CONTAMINAÇÃO DETECTADO: ", m[id][1], "(CPF: ", m[id][2], ")", "esteve no mesmo local e no mesmo dia que um dos pacientes infectados com COVID-19. Favor contatar para realizar um novo teste.\n")
					riscos++
				}
			}
		}
		se(riscos == 0){
			escreva("Não foram detectados riscos de contaminação\n")
		}
	}

	funcao salvarDados(cadeia m[][]){
		inteiro endereco = arq.abrir_arquivo("usuarios.txt", arq.MODO_ESCRITA)
		para(inteiro i = 0;i < iglobal;i++){
			para(inteiro j = 0;j < COL_US;j++){
				se(m[i][j] != ""){
					arq.escrever_linha(m[i][j], endereco)
				}
			}
		}
		arq.fechar_arquivo(endereco)
	}
	
	funcao inicio()
	{
		cadeia usuarios[MAX_US][COL_US]
		cadeia estabs[MAX_ESTAB][COL_ESTAB]
		carregarDados(usuarios, estabs)
		inteiro op = 0
		faca{
			menu()
			leia(op)
			escolha(op){
				caso 1:
					cadastrarUsuario(usuarios, &iglobal)
					pare

				caso 2:
					listagemUsuarios(usuarios)
					escreva("\n\nAperte enter para sair da listagem")
					leia(input)
					limpa()
					pare

				caso 3:
					limpa()
					listagemEstab(estabs)
					escreva("\n\nAperte enter para sair da listagem")
					leia(input)
					limpa()
					pare

				caso 4:
					checkIn(usuarios)
					limpa()
					pare

				caso 5:
					checarRisco(usuarios)
					escreva("\nAperte enter para continuar.\n")
					leia(input)
					pare

				caso 0:
					escreva("Saindo...\n")
					salvarDados(usuarios)
					pare

				caso contrario:
					escreva("Opção inválida\n")
					pare
			}
		}
		enquanto(op != 0)
	}
}
/* $$$ Portugol Studio $$$ 
 * 
 * Esta seção do arquivo guarda informações do Portugol Studio.
 * Você pode apagá-la se estiver utilizando outro editor.
 * 
 * @POSICAO-CURSOR = 5539; 
 * @PONTOS-DE-PARADA = ;
 * @SIMBOLOS-INSPECIONADOS = ;
 * @FILTRO-ARVORE-TIPOS-DE-DADO = inteiro, real, logico, cadeia, caracter, vazio;
 * @FILTRO-ARVORE-TIPOS-DE-SIMBOLO = variavel, vetor, matriz, funcao;
 */