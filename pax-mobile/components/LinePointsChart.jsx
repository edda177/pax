import { CartesianChart, Area } from "victory-native";
import DATA from "../data/roomdata.json";

export function LinePointsChart() {
  return (
    <CartesianChart data={DATA} xKey="x" yKeys={["y"]}>
      {({ points, chartBounds }) => (
        //👇 pass a PointsArray to the Line component, y0, as well as options.
        <Area
          points={points.y}
          y0={chartBounds.bottom}
          color="rgb(250, 216, 113)"
          animate={{ type: "timing", duration: 300 }}
        />
      )}
    </CartesianChart>
  );
}