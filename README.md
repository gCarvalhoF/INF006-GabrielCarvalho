# **INF006 - Estrutura de dados e Algoritmo**

<!---Esses são exemplos. Veja https://shields.io para outras pessoas ou para personalizar este conjunto de escudos. Você pode querer incluir dependências, status do projeto e informações de licença aqui--->

![GitHub repo size](https://img.shields.io/github/repo-size/gcarvalhof/INF006-GabrielCarvalho?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/gcarvalhof/INF006-GabrielCarvalho?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/gcarvalhof/INF006-GabrielCarvalho?style=for-the-badge)

> Repositório feito para armazenar trabalhos e atividades referentes à disciplina de Estrutura de dados e Algoritmo do curso de tecnólogo em ADS (*Análise e desenvolvimento de sistemas*) do IFBA (*Instituto Federal da Bahia*), ministrada pelo professor Antônio Carlos.

## Atividades desenvolvidas

### Foi proposto um trabalho de conclusão de disciplina que constava em criar um sistema para emular um mercado de ações digital desenvolvido na linguagem C.

### **Exigências do trabalho**:

- [x]  Incluir as ofertas online com tipo (compra ou venda), sigla do papel, quantidade e valor usando estrutura de dados dinâmicas.
- [x]  Mostrar as ofertas disponiveis de pelo menos trés titulos varrendo as estrutura de dados dinamicas.
- [ ]  realização de operações pela média (se o valor da compra for maior que o valor de venda)
- [x]  Carregar as ofertas de compra e venda de ações de um ou mais titulos via arquivo
- [x]  Realizar as operacões se
  - [x]  o valor de compra e venda for igual
  - [x]  A quantidade vendida ou comprada é a menor das duas quantidades
  - [x]  Ao realizar a operação, a ordem de compra e venda devem ter as quantidades realizadas abatidas da oferta
- [x]  Apresentar o último preço da operação realizada (cotação) por papel.
    
### **Conceitos trabalhados**:

  - Struct
  - Alocação dinâmica
  - Ponteiros
  - Funções
  - Tipos de dados
  - Retorno e tratamento de arrays em funções
  - Tratamento de arquivos
    - Recuperação de dados inseridos em arquivos

## 🚀 Instalando <Simulador_de_Mercado_Financeiro>

Para instalar o <Simulador_de_Mercado_Financeiro>, siga estas etapas:

Linux e macOS:
```
gcc trabalhoFinal.c -o mercadoAcoes
```

Windows:
```
gcc trabalhoFinal.c -o mercadoAcoes
```

## ☕ Usando <Simulador_de_Mercado_Financeiro>

Para usar <Simulador_de_Mercado_Financeiro>, siga estas etapas:

```
./mercadoAcoes
```

### **Os arquivos de dados seguem um padrão próprio:**
    - Para inserir um novo título segue-se o modelo:
       < id > < sigla > 
       (  3     MGLU3 )
    - Já para a inserção de operações segue-se o modelo:
       < id do titulo > < valor > < qtd > < tipo > 
       (      0           15.50     140      c   )

Os menus são intuitivos, sinta-se livre para inserir novas ações no [arquivo de títulos](./titulos.txt) ou novas operações (compra e venda) no [arquivo de operações](acoes.txt)

## Exemplo prático

[Vídeo de execução do programa.](https://youtu.be/XtoiHSkq2B0)


## 🤝 Desenvolvedor

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/gcarvalhof">
        <img src="https://avatars.githubusercontent.com/u/68783301?v=4" width="100px;" alt="Foto do Iuri Silva no GitHub"/><br>
        <sub>
          <b>Gabriel Carvalho</b>
        </sub>
      </a>
    </td>
  </tr>
</table>

[⬆ Voltar ao topo](#nome-do-projeto)<br>