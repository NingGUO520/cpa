set encoding utf8
set terminal pdf
set output "res_in_degres.pdf"
# set output "res_alphas_0_15-0_90.pdf"
set border linewidth 1.5

set title "Corrélation entre le degré entrant et le page rank"
# set title "Rapport de deux page rank différents : "
set xlabel 'Page rank pour α = 0.15'
set ylabel 'Le degré entrant'
# set ylabel 'Page rank pour α = 0.9'

set yrange[0:*]

plot 'res_in_degree.txt' title "Rapport entre les résultats de page rank et le degré entrant"
# plot 'res_two_alphas.txt' title "Rapport des rangs obtenus pour des α différents"
