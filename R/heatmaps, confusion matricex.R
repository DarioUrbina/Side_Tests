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

colors = heat.colors(256)

str(mtcarr)
rownames(mtcars)    
colnames(mtcars)
as.matrix(mtcars)
heatmap(as.matrix(mtcars)
     ,scale = "column"
     ,col = heat.colors(256)
     ,main = "Characteristics of car models"
     ,Rowv = NA
     ,Colv = NA
     )
