import { Pressable, View, Text } from "react-native";

export default function Home() {
	return (
		<View style={{ flex: 1, alignItems: "center", justifyContent: "center" }}>
			<Pressable style={{ backgroundColor: "green", borderRadius: 2, padding: 8 }} onPress={() => console.log("called server!")}>
				<Text style={{ color: "white" }}>
					Call Server
				</Text>
			</Pressable>
		</View>
	)
}
