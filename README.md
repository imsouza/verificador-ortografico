# Verificador Ortografico

Projeto desenvolvido para a disciplina de Estruturas de Dados da UFES que realiza a verificação ortográfica de arquivos de textos com base no dicionário passado para fins de análise de desempenho.

## Observação
Tanto as entradas de dados disponíveis em [/input] quanto os dicionários disponíveis em [/dics] podem ser modificados livremente e/ou adicionado novos fazendo as devidas alterações na execução.

## Estruturas usadas para comparação de desempenho
- Lista
- Árvore Binária de Busca
- Árvore AVL

## Parâmetros de linha de comando
Por padrão, ao executar o código sem parâmetros será utilizada a estrutura de Árvore Binária de Busca (ABB) para o processamento dos dados.

- -avl: Executa o código utilizando a estrutura de árvore AVL

## Executar
Obs.: tanto os parâmetros quanto os arquivos de dicionário e entrada podem ser alterados no Makefile.

#### Compilar
```$ make && make run```

#### Checar memory leaks

```$ make && make memcheck```

#### Limpar arquivos .o
 
```$ make clean```

## Análise gráfica de teste de desempenho
Obs.: todos gráficos estão disponíveis em [/plots]

#### Dicionário pt-BR
![abb-completa-pt](https://user-images.githubusercontent.com/39147407/118263033-1e32d100-b48c-11eb-940a-318ce236bbc3.png)

![avl-completa-pt](https://user-images.githubusercontent.com/39147407/118263064-28ed6600-b48c-11eb-8186-55177eed9e2f.png)

#### Dicionário en-US
![abb-completa-en](https://user-images.githubusercontent.com/39147407/118263131-402c5380-b48c-11eb-9f11-627ecc3b12a8.png)

![avl-completa-en](https://user-images.githubusercontent.com/39147407/118263156-47ebf800-b48c-11eb-8e99-8aae778c234e.png)

## OS Suporte

Linux

## Autor

Mateus Almeida

## Licença

This project is licensed under the [MIT](https://github.com/imsouza/verificador-ortografico/blob/main/LICENSE) License.