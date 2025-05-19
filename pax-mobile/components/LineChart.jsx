import { LineChart } from "react-native-gifted-charts";
import react from "react";
import { View } from "react-native":

const LineChart = () => {
  const data = [
    {value: 5, label: '08:00'},
    {value: 3, label: '10:00'},
    {value: -2, label: '12:00'},
    {value: -3, label: '14:00'},
    {value: 2, label: '16:00'},
    {value: 3, label: '18:00'},
  ];
  
export default LineChart

  return 
  (
  <View style={styles.container}>
    <Text style={{color: textPrimary, fontWeight: "600", fontSize: 8}}>
         Rummets luftkvalité idag
        </Text>
  <LineChart data={data} />
  </View>
  )
}

const createStyles = () =>
  StyleSheet.create({
      container: {
      flex: 1,
      backgroundColor: "#061a17",
      paddingBottom: 150,
      alignItems: "center",
      justifyContent: "center",
      flexDirection: "column",
      paddingTop: "20%",
    }
    })
