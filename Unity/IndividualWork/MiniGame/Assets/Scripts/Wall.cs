using UnityEngine;
using System.Collections;

public class Wall : MonoBehaviour {

    public float speed;
    private int cnt = 0;
	// Use this for initialization
	void Start ()
    {
    	cnt++;
		Destroy(gameObject, 10f);
	}
	
	// Update is called once per frame
	void Update ()
    {
        transform.Translate(speed * Time.deltaTime, 0, 0);
	}
	public int GetScore()
	{
		return cnt;
	}
}
