

import pandas as pd
import csv

from geopy.geocoders import Nominatim
from geopy.distance import geodesic
geolocator = Nominatim(user_agent="Eventure")

from __future__ import division
import numpy as np
import math

import collections
trainingCsvPath = "Documents/Events/finalCsvs/training.csv"
usersCsvPath = "Documents/Events/finalCsvs/users.csv"
eventsCsvPath = "Documents/Events/finalCsvs/events.csv"

#--------------------------------------------------------------------------------
# BHATTACHARYA
#--------------------------------------------------------------------------------

def compute_relevence_feature(userPastEvents, upcomingEventName, eventsCsv):

    avg_word_hist = compute_avg_hist_of_past_events(userPastEvents, eventsCsv)
    upcoming_event_word_hist = get_event_word_hist(upcomingEventName, eventsCsv)
    event_similarity = compute_bhattacharya_similarity(avg_word_hist, upcoming_event_word_hist)
    return event_similarity # 0..1

def normalize(h):
    #normalizedList = []
   # for x in h:
        
    return [x / float(np.sum(h)) if np.sum(h)!=0 else x / float(1) for x in h]

def compute_bhattacharya_similarity(h1, h2):
    h1_normal = normalize(h1)
    h2_normal = normalize(h2)
    
    return np.sum(np.sqrt(np.multiply(h1_normal, h2_normal)))

def compute_avg_hist_of_past_events(userPastEvents, eventsCsv):
    #past_events_ids = get_past_events_of_user(uid)
    userPastEventsList = userPastEvents.split(",")
    #print("past list: ", userPastEventsList)
    past_events_word_hists = [get_event_word_hist(eventName, eventsCsv) for eventName in userPastEventsList]
   # print("past hist: ", past_events_word_hists)
    avgHistPast = np.mean(past_events_word_hists, axis=0)
   # print("avg past hist: ", avgHistPast)
    return np.mean(past_events_word_hists, axis=0)


def get_event_word_hist(eventName_1, eventsCsv):
    #print("eventname_1: ", eventName_1)
    for eventRecord in eventsCsv.iterrows():
        eventRecord = eventRecord[1]
        eventName = eventRecord['event_name']
      #  print("rec: ", eventName)
        #print
        if(eventName.strip().lower() == eventName_1.strip().lower()):
          #  print("for: ", eventName.lower())
            eventDescription = eventRecord['description']
           # print("desc: ", eventDescription)
            return getWordCount(eventDescription, eventName)
    
def getWordCount(eventDesc, eventName):
   # print("in getWordCount()", eventName)
    listOfSignificantWords = ["fair", "business", "job", "career", "entrepreneurs", "professional", "free", "positions", "dance", "art", "creative", "fun", "flamenco", "workshop", "dancers", "experience", "tech", "technologies", "silicon",  "valley", "technology", "women", "innovative", "cloud", "ai"]
    count = collections.Counter()

    wordCounts = [eventDesc.count(word) for word in listOfSignificantWords]

    #print("wordCounts: ", wordCounts)
    return wordCounts
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------

def computeFeatures(tUserName, tEventName, usersCsvPath, eventsCsvPath):
    print("user: ", tUserName, " event: ", tEventName)
    usersCsv = pd.read_csv(usersCsvPath)
    eventsCsv = pd.read_csv(eventsCsvPath)

    for userRecord in usersCsv.iterrows():
        userRecord = userRecord[1]
        userName = userRecord['user_name']
        if(userName.lower() == tUserName.lower()):
            userLocation = userRecord['user_location']
            print("user loc: ", userLocation)
            userPastEvents = userRecord['past_event_names']
            
    for eventRecord in eventsCsv.iterrows():
        eventRecord = eventRecord[1]
        eventName = eventRecord['event_name']
        if(eventName.lower() == tEventName.lower()):
            eventLocation = eventRecord['event_location']
            print("event loc: ", eventLocation)
            #histogram
            upcomingEventName = eventName.lower()
           # print(upcomingEventDescription)
    
    #call tProximity = calculateProximity(userLocation, eventLocation)
    #call tRelevance = calculateRelevance(?,?)
    tProximity = calculateProximity(userLocation, eventLocation)
    tRelevance = calculateRelevanceBetweenCurrentAndPastEvents(upcomingEventName, userPastEvents, eventsCsv)
    print("tRelevance: ", tRelevance)
    #relevance
    featureVector = [tUserName, tEventName, tProximity, tRelevance]
    return featureVector

def calculateProximity(userLocation, eventLocation):
    uLocation = geolocator.geocode(userLocation)
    eLocation = geolocator.geocode(eventLocation)
    print("uloc: ", uLocation)
    print("eloc: ", eLocation)
    
    userLatitude = int(uLocation.latitude)
    userLongitude = int(uLocation.longitude)
    print("user lat: ", userLatitude)
    
    eventLatitude = int(eLocation.latitude)
    eventLongitude = int(eLocation.longitude)
    print("event lat: ", eventLatitude)
    
    
    userCoordinates = (userLatitude, userLongitude)
    print("user coordinates: ", userCoordinates)
    eventCoordinates = (eventLatitude, eventLongitude)
    print("event coordinates: ", eventCoordinates)
   # print("user past events", userPastEvents)

    distance = geodesic(userCoordinates, eventCoordinates).miles
    print("distance: ", distance)
    
    return distance
    
def calculateRelevanceBetweenCurrentAndPastEvents(upcomingEventName, userPastEvents, eventsCsv):
    return compute_relevence_feature(userPastEvents, upcomingEventName, eventsCsv)

def prepareDataForWatsonTraining(trainingCsvPath, usersCsvPath, eventsCsvPath):
    trainingCsv = pd.read_csv(trainingCsvPath)
    
    #create a csv file

    with open('Documents/Events/finalCsvs/testTrainingData.csv', mode='w') as testTrainingData:
        csvWriter = csv.writer(testTrainingData, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

        for trainingDataRow in trainingCsv.iterrows():
            trainingDataRow = trainingDataRow[1]
            featureVector = computeFeatures(trainingDataRow['user_name'], trainingDataRow['event_name'], usersCsvPath, eventsCsvPath)    
            csvWriter.writerow([featureVector[0], featureVector[1], featureVector[2], featureVector[3]]) #add featureVector[1] later
        
        return testTrainingData

finalTrainingData = prepareDataForWatsonTraining(trainingCsvPath, usersCsvPath, eventsCsvPath)
