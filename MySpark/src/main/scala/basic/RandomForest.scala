package main.scala.basic

import org.apache.log4j.{Level, Logger}
import org.apache.spark.ml.Pipeline
import org.apache.spark.ml.classification.{RandomForestClassificationModel, RandomForestClassifier}
import org.apache.spark.ml.evaluation.MulticlassClassificationEvaluator
import org.apache.spark.ml.feature.{IndexToString, VectorIndexer, StringIndexer}
import org.apache.spark.sql.SparkSession

/**
 * 随机森林
 * 参数1：提交到本地还是集群。"local" 或 "local[*]" -- 本地执行；  "--master spark://master:7077" -- 集群执行
 * 参数2：文件名（本地或者是hdfs）。"C:/Workspace/MySparkApplication/data/libsvmDataSet.txt" -- 本地数据文件夹;  "hdfs://master:9000/user/root/data/libsvmDataSet.txt"
 * 参数3：保存模型地址（本地或者是hdfs）。"C:/Workspace/MySparkApplication/data/module/rfmodule" -- 本地数据文件夹;  "hdfs://master:9000/user/root/data/module/rfmodule"
 * IDEA本地运行参数设置："local C:/Workspace/MySparkApplication/data/libsvmDataSet.txt C:/Workspace/MySparkApplication/data/module/rfmodule"
 * Spark集群提交jar运行命令：
spark-submit --master spark://master:7077 \
--class main.scala.basic.RandomForest \
--executor-memory 1g \
/root/MySparkApplication.jar \
spark://master:7077 \
hdfs://master:9000/user/root/data/libsvmDataSet.txt > RandomForestsResult.log

 */
object RandomForest {
  def main(args: Array[String]) {
    Logger.getLogger("org").setLevel(Level.ERROR)
    // 创建Spark对象
    val spark = SparkSession.builder()
      .appName("RandomForest")
      .master(args(0))
      .getOrCreate()

    // 获取数据libsvm
    val data = spark.read.format("libsvm")
      .load(args(1))
    print("show data:")
    data.show()
    print("data schema:")
    data.printSchema()

    // 标识整个数据集的标识列和索引列
    val labelIndexer = new StringIndexer()
      .setInputCol("label")
      .setOutputCol("indexedLabel")
      .fit(data)

    // 设置树的最大层次
    val featureIndexer = new VectorIndexer()
      .setInputCol("features")
      .setOutputCol("indexedFeatures")
      .setMaxCategories(4)
      .fit(data)

    // 拆分数据为训练集和测试集（7:3）
    val Array(trainingData, testData) = data.randomSplit(Array(0.7, 0.3))
    testData.show(5)

    // 创建模型（设置决策树的个数:10）
    val randomForest = new RandomForestClassifier()
      .setLabelCol("indexedLabel")
      .setFeaturesCol("indexedFeatures")
      .setNumTrees(10)

    // 转化初始数据
    val labelConverter = new IndexToString()
      .setInputCol("prediction")
      .setOutputCol("predictedLabel")
      .setLabels(labelIndexer.labels)

    // 使用管道运行转换器和随机森林算法
    val pipeline = new Pipeline()
      .setStages(Array(labelIndexer, featureIndexer, randomForest, labelConverter))

    // 训练模型
    val model = pipeline.fit(trainingData)

    // 预测
    val predictions = model.transform(testData)
    // 输出预测结果
    predictions.select("predictedLabel", "label", "features").show(5)
    // 创建评估函数，计算错误率
    val evaluator = new MulticlassClassificationEvaluator()
      .setLabelCol("indexedLabel")
      .setPredictionCol("prediction")
      .setMetricName("accuracy")
    // 评估准确率
    val accuracy = evaluator.evaluate(predictions)
    println("test error = " + (1.0 - accuracy))
    val rfModel = model.stages(2).asInstanceOf[RandomForestClassificationModel]
    println("learned classification forest model:\n" + rfModel.toDebugString)

    // 保存模型
//    model.write.overwrite().save("C:/Workspace/MySparkApplication/data/module/rfmodule")
    model.write.overwrite().save(args(2))

    spark.stop()
  }
}