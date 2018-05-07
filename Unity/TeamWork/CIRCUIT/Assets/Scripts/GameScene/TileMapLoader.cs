using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Xml;


public class TileMapLoader : MonoBehaviour
{
	[System.Serializable]
	public class TileRankData
	{
		public TextAsset[] stageData = new TextAsset[5];
	}

	public class LayerData
	{
		public int x = 0;
		public int y = 0;
		public int data = 0;
	}

	[SerializeField]
	private GameObject tile_;

	[SerializeField]
	private TileRankData[] tileData_ = new TileRankData[10];

	[SerializeField]
	private Sprite[] tileSprite_;
	[SerializeField, Tooltip("ワープの半径")]
	private float warpColliderRadius_ = 3.250f;

	[SerializeField]
	private float parentScale_ = 0.40f;


	private List<XmlAttributeCollection> mapAttr_ = new List<XmlAttributeCollection>();
	private List<XmlAttributeCollection> tileAttr_ = new List<XmlAttributeCollection>();

	private List<LayerData> layerData_ = new List<LayerData>();


	private GameObject tileObject_;
	public void Create(int rankNum = 0, int stageNum = 0)
	{
		Load(rankNum, stageNum);
		DrawTileMap();
	}

	// TODO: 関数化
	public void Load(int rankNum, int stageNum)
	{
		XmlDocument xmlData = new XmlDocument();
		xmlData.LoadXml(tileData_[rankNum].stageData[stageNum].text);

		XmlNodeList mapList = xmlData.GetElementsByTagName("map");
		foreach (XmlNode map in mapList)
		{
			XmlNodeList childList = map.ChildNodes;
			foreach (XmlNode child in childList)
			{
				if (child.Name == "tileset")
				{
					tileAttr_.Add(child.Attributes);
				}

				if (child.Name == "layer")
				{
					mapAttr_.Add(child.Attributes);
					Vector2 size = new Vector2();

					XmlNode node = child.FirstChild;
					XmlNode textNode = node.FirstChild;
					string text = textNode.Value;
					AnalysisMapCSV(text);
				}
			}
		}
	}

	private void AnalysisMapCSV(string textData)
	{
		int y = 0;
		foreach (string line in textData.Split('\n'))
		{
			int x = 0;
			foreach (string separat in line.Split(','))
			{
				int data;
				if (!int.TryParse(separat, out data)) continue;

				LayerData layerTileData = new LayerData();
				layerTileData.x = x;
				layerTileData.y = y;
				layerTileData.data = data;

				layerData_.Add(layerTileData);

				x++;
			}
			y++;
		}
	}

	private void DrawTileMap()
	{
		CheckLayerData();
	}

	private void CheckLayerData()
	{
		foreach (var layerData in layerData_)
		{
			if (layerData.data == 0) continue;


			tileObject_ = Instantiate(tile_);

			string spriteName = tileAttr_[layerData.data - 1].GetNamedItem("name").Value;
			int num = 0;
			foreach (Sprite sprite in tileSprite_)
			{
				if (sprite.name != spriteName)
				{
					num++;
					continue;
				}

				tileObject_.GetComponent<SpriteRenderer>().sprite = tileSprite_[num];
				tileObject_.gameObject.tag = TagSetting(tileSprite_[num].name);
				tileObject_.name = tileObject_.gameObject.tag;
			}

			SpriteRenderer renderSprite = tileObject_.GetComponent<SpriteRenderer>();
			if (renderSprite.sprite.name == "START" || renderSprite.sprite.name == "GOAL" || renderSprite.sprite.name == "miti")
			{
				tileObject_.transform.position = new Vector3((int.Parse(tileAttr_[layerData.data - 1].GetNamedItem("tilewidth").Value) * layerData.x / 100) * tile_.transform.localScale.x, (10 - (int.Parse(tileAttr_[layerData.data - 1].GetNamedItem("tileheight").Value) * layerData.y / 100)) * tile_.transform.localScale.y, 2.0f);
			}
			else
			{
				tileObject_.transform.position = new Vector3((int.Parse(tileAttr_[layerData.data - 1].GetNamedItem("tilewidth").Value) * layerData.x / 100) * tile_.transform.localScale.x, (10 - (int.Parse(tileAttr_[layerData.data - 1].GetNamedItem("tileheight").Value) * layerData.y / 100)) * tile_.transform.localScale.y, 1.0f);
			}

			if (renderSprite.sprite.name == "WARP")
			{
				tileObject_.AddComponent<WarpManager>();
				tileObject_.GetComponent<SpriteRenderer>().sortingOrder = 0;
				tileObject_.transform.position = new Vector3(tileObject_.transform.position.x, tileObject_.transform.position.y, 0.0f);
				tileObject_.GetComponent<BoxCollider2D>().enabled = false;
				tileObject_.AddComponent<CircleCollider2D>().radius = warpColliderRadius_;
				tileObject_.GetComponent<CircleCollider2D>().isTrigger = true;
			}

			tileObject_.transform.SetParent(transform);
		}

		gameObject.transform.localScale = new Vector3(parentScale_, parentScale_, 1.0f);
	}

	private string TagSetting(string name)
	{
		if (name == "START") return "Start";
		if (name == "GOAL") return "Goal";
		if (name == "WARP") return "Warp";
		return "Road";
	}
}
