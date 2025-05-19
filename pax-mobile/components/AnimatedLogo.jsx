import React from "react";
import { StyleSheet, View, Image } from "react-native";
import Animated, {
  useSharedValue,
  useAnimatedStyle,
  withRepeat,
  withTiming,
  Easing,
} from "react-native-reanimated";

const AnimatedLogo = () => {
  const scale = useSharedValue(1);

  // Starta looping-animationen direkt
  React.useEffect(() => {
    scale.value = withRepeat(
      withTiming(1.1, {
        duration: 1500,
        easing: Easing.inOut(Easing.ease),
      }),
      -1, // oändlig loop
      true // vända fram och tillbaka (pingpong)
    );
  }, []);

  const animatedStyle = useAnimatedStyle(() => {
    return {
      transform: [{ scale: scale.value }],
    };
  });

  return (
     <View style={styles.container}>
    <Animated.Image
      source={require("../assets/logo/pax_logo-17.png")}
      style={[styles.image, animatedStyle]}
      resizeMode="cover"
    />
    </View>
  );
};

export default AnimatedLogo;

const styles = StyleSheet.create({
  image: {
    maxWidth: 220,
    maxHeight: 200,
  },
      container: {
      flex: 1,
      backgroundColor: "#061a17",
      paddingBottom: 150,
      alignItems: "center",
      justifyContent: "center",
      flexDirection: "column",
      paddingTop: "20%",
    },
});
