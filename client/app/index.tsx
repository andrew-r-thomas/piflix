import { Pressable, View, Text } from "react-native";

export default function Home() {
	const simpleCall = async () => {
		console.log("called server");
		const resp = await fetch("http://192.168.50.68:8080");
		const text = await resp.text();
		console.log(`server responded with: ${text}`);
	}
	return (
		<View style={{ flex: 1, alignItems: "center", justifyContent: "center" }}>
			<Pressable style={{ backgroundColor: "green", borderRadius: 2, padding: 8 }} onPress={simpleCall}>
				<Text style={{ color: "white" }}>
					Call Server
				</Text>
			</Pressable>
		</View>
	)
}
