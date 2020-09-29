package server_test

import (
	"encoding/json"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"

	"github.com/gorilla/mux"

	"sketch-app/typeahead-golang/app/core"
	"sketch-app/typeahead-golang/app/data"
	"sketch-app/typeahead-golang/app/handler"
	"sketch-app/typeahead-golang/app/model"
)

type ServerTest struct {
	mux      *mux.Router
	recorder *httptest.ResponseRecorder
	factory  handler.Factory
	size     int
}

func (st *ServerTest) setUp() {
	// create factories
	mf := model.MakeFactory()
	st.factory = handler.MakeFactory()
	st.factory.SetModelFactory(mf)

	// define parameters
	st.size = 3

	// create http mock
	st.mux = mux.NewRouter()

	// config handler
	haags := st.factory.Create(core.GetAllAliasSuggestionKind)
	st.mux.Handle(haags.Path(), haags).Methods(haags.Methods())

	hags := st.factory.Create(core.GetAllSuggestionKind)
	st.mux.Handle(hags.Path(), hags).Methods(hags.Methods())

	hgs := st.factory.Create(core.GetPrefixSuggestionKind)
	st.mux.Handle(hgs.Path(), hgs).Methods(hgs.Methods())

	hss := st.factory.Create(core.SetSuggestionKind)
	st.mux.Handle(hss.Path(), hss).Methods(hss.Methods())
}

func (st *ServerTest) setUpTest() {
	// create recorder
	st.recorder = httptest.NewRecorder()

	// generate data
	input := []*data.Suggestion{
		{Name: "aa", Times: 10},
		{Name: "ab", Times: 10},
		{Name: "ac", Times: 11},
		{Name: "acd", Times: 12},
		{Name: "ba", Times: 11},
		{Name: "bb", Times: 12},
		{Name: "bc", Times: 13},
	}

	model.CreateContainer(st.size)
	model.PopulateContainerValues(input)
}

func (st *ServerTest) TestGetAllAliasSuggestion(t *testing.T) {
	// result of the test
	answer := []*data.Suggestion{
		{Name: "Bc", Times: 13},
		{Name: "Acd", Times: 12},
		{Name: "Bb", Times: 12},
	}

	// perform test
	request, _ := http.NewRequest(http.MethodGet, "/typeahead/", nil)
	st.mux.ServeHTTP(st.recorder, request)

	// verify response code
	if st.recorder.Code != 200 {
		t.Errorf("Response code is %v", st.recorder.Code)
	}

	// read body request
	var response []*data.Suggestion
	json.Unmarshal(st.recorder.Body.Bytes(), &response)

	// verify test size
	if len(answer) != len(response) {
		t.Errorf("size mismatch %d - %d", len(answer), len(response))
	}

	// verify answer values
	for i, v := range response {
		if answer[i].Name != v.Name {
			t.Errorf("name mismatch: %s - %s", answer[i].Name, v.Name)
		}
		if answer[i].Times != v.Times {
			t.Errorf("times mismatch: %d - %d", answer[i].Times, v.Times)
		}
	}
}

func (st *ServerTest) TestGetAllSuggestion(t *testing.T) {
	// result of the test
	answer := []*data.Suggestion{
		{Name: "Bc", Times: 13},
		{Name: "Acd", Times: 12},
		{Name: "Bb", Times: 12},
	}

	// perform test
	request, _ := http.NewRequest(http.MethodGet, "/typeahead", nil)
	st.mux.ServeHTTP(st.recorder, request)

	// verify response code
	if st.recorder.Code != 200 {
		t.Errorf("Response code is %v", st.recorder.Code)
	}

	// read body request
	var response []*data.Suggestion
	json.Unmarshal(st.recorder.Body.Bytes(), &response)

	// verify test size
	if len(answer) != len(response) {
		t.Errorf("size mismatch %d - %d", len(answer), len(response))
	}

	// verify answer values
	for i, v := range response {
		if answer[i].Name != v.Name {
			t.Errorf("name mismatch: %s - %s", answer[i].Name, v.Name)
		}
		if answer[i].Times != v.Times {
			t.Errorf("times mismatch: %d - %d", answer[i].Times, v.Times)
		}
	}
}

func (st *ServerTest) TestGetSuggestion(t *testing.T) {
	// result of the test
	answer := []*data.Suggestion{
		{Name: "Acd", Times: 12},
		{Name: "Ac", Times: 11},
		{Name: "Aa", Times: 10},
	}

	// perform test
	request, _ := http.NewRequest(http.MethodGet, "/typeahead/a", nil)
	st.mux.ServeHTTP(st.recorder, request)

	// verify response code
	if st.recorder.Code != 200 {
		t.Errorf("Response code is %v", st.recorder.Code)
	}

	// read body request
	var response []*data.Suggestion
	json.Unmarshal(st.recorder.Body.Bytes(), &response)

	// verify test size
	if len(answer) != len(response) {
		t.Errorf("size mismatch %d - %d", len(answer), len(response))
	}

	// verify answer values
	for i, v := range response {
		if answer[i].Name != v.Name {
			t.Errorf("name mismatch: %s - %s", answer[i].Name, v.Name)
		}
		if answer[i].Times != v.Times {
			t.Errorf("times mismatch: %d - %d", answer[i].Times, v.Times)
		}
	}
}

func (st *ServerTest) TestSetSuggestion(t *testing.T) {
	// result of the test
	answer := &data.Suggestion{Name: "Aa", Times: 11}

	// perform test
	input := strings.NewReader(`{"name": "Aa"}`)
	request, _ := http.NewRequest(http.MethodPost, "/typeahead", input)
	st.mux.ServeHTTP(st.recorder, request)

	// verify response code
	if st.recorder.Code != 200 {
		t.Errorf("Response code is %v", st.recorder.Code)
	}

	// read body request
	var response data.Suggestion
	json.Unmarshal(st.recorder.Body.Bytes(), &response)

	// verify answer values
	if answer.Name != response.Name {
		t.Errorf("name mismatch: %s - %s", answer.Name, response.Name)
	}
	if answer.Times != response.Times {
		t.Errorf("times mismatch: %d - %d", answer.Times, response.Times)
	}
}

func (st *ServerTest) TestGetSuggestionWithoutMatch(t *testing.T) {
	// perform test
	request, _ := http.NewRequest(http.MethodGet, "/typeahead/abcdefg", nil)
	st.mux.ServeHTTP(st.recorder, request)

	// verify response code
	if st.recorder.Code != 200 {
		t.Errorf("Response code is %v", st.recorder.Code)
	}

	// verify content type
	if h, ok := st.recorder.Header()["Content-Type"]; !ok {
		t.Error("Content-Type is not application/json")
	} else if len(h) == 0 && h[0] != "application/json" {
		t.Error("Content-Type is not application/json")
	}

	// verify body request
	body := st.recorder.Body.Bytes()
	if len(body) != 2 {
		t.Error("empty array is not in the body of the response")
	}
	if body[0] != '[' && body[1] != ']' {
		t.Error("empty array is not in the body of the response")
	}
}

func TestAll(t *testing.T) {
	st := &ServerTest{}

	st.setUp()

	st.setUpTest()
	t.Run("GetAllAliasSuggestion", st.TestGetAllAliasSuggestion)

	st.setUpTest()
	t.Run("GetAllSuggestion", st.TestGetAllSuggestion)

	st.setUpTest()
	t.Run("GetSuggestion", st.TestGetSuggestion)

	st.setUpTest()
	t.Run("GetSuggestionWithoutMatch", st.TestGetSuggestionWithoutMatch)

	st.setUpTest()
	t.Run("SetSuggestion", st.TestSetSuggestion)
}
