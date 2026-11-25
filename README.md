## Sistema de Gerenciamento de Senhas de Atendimento Clínico

## Objetivo

Desenvolver um sistema em linguagem C para gerenciar senhas de atendimento de uma clínica médica, permitindo cadastrar pacientes, classificá-los por prioridade e organizar a fila de atendimento.

## Funcionalidades
Cadastro de pacientes.
Classificação automática em três categorias:
Normal (N).
Preferencial (P).
Urgente (U).
Geração de senhas sequenciais independentes.
Consulta da próxima senha.
Chamada de pacientes.
Finalização de atendimentos.
Painel de acompanhamento das filas.
Controle de prioridade e ordem FIFO.
## Regras de classificação
Urgente: pacientes com idade superior a 80 anos.
Preferencial: gestantes, lactantes, pessoas com necessidades especiais, pessoas com obesidade, mulheres com 60 anos ou mais e homens com 65 anos ou mais.
Normal: pacientes que não se enquadram nas categorias anteriores.

A categoria urgente possui prioridade sobre a preferencial, que possui prioridade sobre a normal.

## Tecnologias utilizadas
Linguagem C.
Estruturas de dados (struct).
Vetores.
Funções.
Estruturas condicionais.
Estruturas de repetição.
Manipulação de strings.
## Funções implementadas
-  Função	Responsabilidade
-  limparBuffer()	Limpar o buffer do teclado
-  lerInteiro()	Validar entradas numéricas
-  lerSimNao()	Validar respostas de sim ou não
-  classificarPaciente()	Definir a prioridade do paciente
-  gerarSenha()	Gerar e armazenar a senha
-  cadastrarPaciente()	Registrar novos pacientes
-  consultarProxima()	Consultar a próxima senha
-  chamarPaciente()	Chamar o próximo paciente
-  finalizarAtendimento()	Finalizar o atendimento atual
-  painel()	Exibir informações das filas
-  menu()	Controlar as opções do sistema
-  main()	Inicializar o programa
## Compilação

É necessário possuir um compilador GCC instalado.

No terminal, execute:

bash
gcc main.c -o clinica -std=c11 -Wall -Wextra

## Execução

No Windows:

bash
clinica.exe


No Linux:

bash
./clinica

## Exemplo de utilização
Execute o programa.
Escolha a opção 1 para cadastrar um paciente.
Informe os dados solicitados.
O sistema classificará automaticamente o paciente.
Uma senha será gerada.
Escolha a opção 5 para visualizar o painel.
Escolha a opção 3 para chamar o próximo paciente.
Escolha a opção 4 para finalizar o atendimento.
## Exemplo de senhas
U001: Urgente.
P001: Preferencial.
N001: Normal.

As senhas são chamadas respeitando a prioridade e a ordem de cadastro dentro de cada categoria.

## Autor

Projeto acadêmico desenvolvido para a avaliação de Algoritmos e Programação em Linguagem C.
