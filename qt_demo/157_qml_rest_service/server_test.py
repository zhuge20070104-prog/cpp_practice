import requests
import json

BASE_URL = "http://localhost:5000"
def test_get_colors(): 
    get_color_url = "{}/colors".format(BASE_URL)
    resp = requests.get(get_color_url)
    result = json.loads(resp.text)
    assert len(result["data"]) == 6, "Get colors failed!"

def test_get_color_by_name():
    get_color_url = "{}/colors/blue".format(BASE_URL)
    resp = requests.get(get_color_url)
    result = json.loads(resp.text)
    assert result["value"] == "#00f", "Get color by name failed!"

def test_create_color():
    create_color_url = "{}/colors".format(BASE_URL)
    color = {"name": "black", "value": "#000"}
    resp = requests.post(create_color_url,json=color)
    result = json.loads(resp.text)
    assert result["value"] == "#000", "Create color failed!"

def test_update_color():
    update_color_url = "{}/colors/blue".format(BASE_URL)
    color = {"value": "#0000fe"}
    resp = requests.put(update_color_url, json=color)
    result = json.loads(resp.text)
    assert result["value"] == "#0000fe", "Update color failed!"


def test_delete_color():
    delete_color_url = "{}/colors/green".format(BASE_URL)
    resp = requests.delete(delete_color_url)
    result = json.loads(resp.text)
    assert result["value"] == "#0f0", "Delete color failed!"
