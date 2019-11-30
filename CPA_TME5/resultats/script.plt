set terminal pdf
set output "res35.pdf"
set border linewidth 1.5

set title "t = 35"

set xlabel "L'indice du sommet"
set ylabel 'Page Rank du sommet'

set yrange[0:*]

set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 pi 1 ps 0.35
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2

# plot 'res_small.txt' with linespoints linestyle 1 title "Distribution des rangs"
plot 'res.txt' with linespoints linestyle 1 title "Distribution des rangs"
