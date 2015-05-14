models <- c("NaiveBayes","NeuralNet","SVM","LogisticRegression","KNearest","MixtureModel")

getData <- function(directory) {
  models <- c("NaiveBayes","NeuralNet","SVM","LogisticRegression","KNearest","MixtureModel")
  datasets <- list()
  for (i in 1:length(models)) {
    datasets[[i]] <- read.table(paste(directory, models[i], ".txt", sep=""), sep="\t", header=TRUE)
  }
  datasets
}

getPCData <- function(directory) {
  models <- c("NaiveBayes","NeuralNet","SVM","LogisticRegression","KNearest","MixtureModel")
  datasets <- list()
  for (i in 1:length(models)) {
    datasets[[i]] <- read.table(paste(directory, models[i], ".txt", sep=""), sep="\t", header=TRUE)
  }
  PCList <- list()
  for (i in 1:ncol(datasets[[1]])) {
    currentlist <- list()
    for (j in 1:length(models)) {
      currentlist[j] <- datasets[[j]][i]
    }
    PC <- data.frame(matrix(unlist(currentlist), nrow=10))
    colnames(PC) <- models
    PCList[[i]] <- PC
  }
  PCList
}

calculateResiduals <- function(df, means) {
  means <- as.numeric(means)
  resid <- df
  for (i in 1:length(means)) {
    resid[,i] <- means[i] - df[,i]
  }
  resid
}

convertToVector <- function(df) {
  vec <- c()
  for (i in 1:ncol(df)) {
    vec <- c(vec, as.numeric(df[,i]))
  }
  vec
}

plotResiduals <- function(directory, dataset) {
  pc <- getPCData(directory)
  df <- pc[[dataset]]
  means <- lapply(df, mean)
  resid <- calculateResiduals(df, means)
  residuals <- convertToVector(resid)
  hist(residuals, main = paste("PC", dataset, " Residuals", sep=""))
}

plotIndCheck <- function(directory, dataset, title = NULL) {
  pc <- getPCData(directory)
  df <- pc[[dataset]]
  means <- as.numeric(lapply(df, mean))
  resid <- calculateResiduals(df, means)
  residuals <- convertToVector(resid)
  if (is.null(title))
    title <- paste("PC", dataset, " Residuals", sep="")
  expected <- rep(means, each=nrow(resid))
  plot(expected, residuals, main = title)
}

formatDataForTest <- function(directory, dataset) {
  pc <- getPCData(directory)
  df <- pc[[dataset]]
  response <- convertToVector(df)
  alternative <- rep(1:6, each=10)
  data = data.frame(response = response, alternative = factor(alternative))
}

plotAnovaTest <- function(directory, dataset, title = NULL) {
  data <- formatDataForTest(directory, dataset)
  aov.fit <- aov(data$response ~ data$alternative)
  if (is.null(title))
    title <- paste("PC", dataset, " Residuals", sep="")
  plot(aov.fit, main = title)
}

anovaTest <- function(directory, dataset) {
  data <- formatDataForTest(directory, dataset)
  aov.fit <- aov(data$response ~ data$alternative)
  summary(aov.fit)
}

tukeyTest <- function(directory, dataset) {
  data <- formatDataForTest(directory, dataset)
  aov.fit <- aov(data$response ~ data$alternative)
  cat(as.numeric(TukeyHSD(aov.fit)[[1]][,4]), sep="\n")
}

plotMeanAccuracy <- function() {
  models <- c("NaiveBayes","NeuralNet","SVM","LogisticRegression","KNearest","MixtureModel")
  accuracy <- c(0.8790284,0.90342864,0.91711522,0.92266538,0.91656084,0.32172642)
  f1 <- c(0.93260964,0.93940994,0.95590466,0.95901562,0.9553374,0.106718608)
  plotdata <- matrix(c(accuracy,f1),nrow=2,byrow=TRUE)
  colnames(plotdata) <- models
  rownames(plotdata) <- c("Accuracy","F1")
  barplot(plotdata, xlab="Classifier", legend = rownames(plotdata), beside=TRUE)
}