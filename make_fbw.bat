cl filtro_bw.c

for /f %%f in ('dir /b in\') do filtro_bw in\%%f out\%%f
