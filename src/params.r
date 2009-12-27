a = read.table("stats.txt")

midf = a[,5] >= 15 & a[,5] <= 15*1.5
bigf = a[,5] > 15*1.5

am = a[midf,]
ab = a[bigf,]

mscore = function(x) {
  lambda = 1/1000
  filt = (am[,3] > x[1]) & (am[,4] < x[2]) & ((am[,4] < x[2]-1 | am[,3] > x[3]))
  return(-(sum(am[filt,5]) - lambda*sum(am[filt,2]^2)))
}

x = optim(c(.7, 8, .8), mscore, method="SANN")
