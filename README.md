| Autor | Edimar Calebe Castanho |
|:-----:|:------:|
| Revisão | 0.1 |
| Ultima alteração | 02/07/2021 |

# Protocolo de comunicação de hidrômetros digitais

Tentei utilizar o protocolo **MODBUS** mas achei muito complicado criar um escravo.

Portanto estou propondo um protocolo mais simples para este projeto. 

Este protocolo é altamente inspirado no **MODBUS**.

## Data Model

| ID | ACTION | LENGTH | DATA | CRC |
|:--:|:------:|:------:|:----:|:---:|
| 1 Byte | 1 Byte | 1 Byte | n Bytes | 2 Bytes |

### ID

Se o ID for 0, isso significa que a mensagem será enviada em modo **broadcast**.
Ou seja, todos os dispositivos irão receber e interpretar a mensagem.

O range dos ID são de 1 a 127.

Se o ID for 0xFF, ou 255. É resposta ao mestre.

Lembrando que as transmissões são sempre iniciadas pelo mestre

### ACTION

O primeiro bit do **ACTION** informa se a ação é de GET ou SET. 

* Se for **1** é **SET**;
* Se for 0 é **GET**;

O restante dos bits será o endereço da informação a ser registrada ou resgatada.

#### Endereços

Lembrando que os endereços são enviados no Byte **ACTION**, onde o primeiro bit representa a operação, e os 7 bits restantes representam o endereço.

Apenas 1 operação pode ser realizada por mensagem.

Por exemplo, para resgatar o número de litros calculados pelo dispositivo de **ID 1** até o momento a mensagem deverá ser o seguinte:

```
0x01 0x02 0x00
```

## GET

| Endereço | Descrição |
|:--------:|:---------:|
| 0x01 | Resgata o número de lítros calculados até o atual momento |
| 0x02 | Resgata o timestamp do dispositivo |

## SET

| Endereço | Descrição |
|:--------:|:---------:|
| 0x02 | Seta o timestamp do distositivo |

### LENGTH

É referente ao tamanho dos dados a serem recebidos.

### DATA

São os dados recebidos pelo protocolo.

### CRC

É o HASH da informação recebida, verificando se a mensagem é integra.

O **CRC** não será implementado no momento pois depende de algorítmos.

