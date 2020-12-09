tb
vector <- rep(0,length(tb)*length(tb))
#vector
count <- 1
for (i in 1:nrow(tb)) {      
  for (j in 1:ncol(tb)) {
    vector[count] <- tb[i,j]
    count <- count+1
  }
}
