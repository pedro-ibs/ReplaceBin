# ReplaceBin
troca textos que estão dentro de um arquivo binario, como um firmuware de microcontrolador 

## *Compilando*
```
~$ gcc main.cpp -o replaceBin
```
## *Executando*
```
~$ replaceBin arquivoalvo.bin O_QUEVAI_SER_SUBISTITUIDO PELO_OQUE_VAI_SER_SUVISTITUIDO
```

### *NOTA:*
os campos O_QUEVAI_SER_SUBISTITUIDO PELO_OQUE_VAI_SER_SUVISTITUIDO devem ter o mesmo tamenho por exemplo

```
~$ replaceBin arquivoalvo.bin 0123456789 9876543210
```
