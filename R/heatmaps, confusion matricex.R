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

str(mtcars)

rownames(mtcars)    
colnames(mtcars)
as.matrix(mtcars)

normalize <- function(x){
  return ((x-min(x))/(max(x)-min(x)))
}

for (i in 1:nrow(tb)){
  tb[,c(i)]<-normalize(tb[,c(i)])
}

#normalize(tb[,c("1")])

zmp.class <- simple_zmp_locations_exp_2.data[,c("ZMP_location")]
simple_zmp_locations_exp_2.data$LC_1

heatmap(as.matrix(mtcars)
     ,scale = "column"
     ,col = rev(heat.colors(256))
     ,main = "Characteristics of car models"
     ,Rowv = NA
     ,Colv = NA
     )
